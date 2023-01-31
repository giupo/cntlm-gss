/*
 * Credentials related structures and routines for the main module of CNTLM
 *
 * CNTLM is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 *
 * CNTLM is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 51 Franklin
 * St, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * Copyright (c) 2007 David Kubicek
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "auth.h"

#include "logger.h"

struct auth_s *new_auth(void) {
	struct auth_s *tmp;

	tmp = (struct auth_s *)malloc(sizeof(struct auth_s));
	if (tmp == NULL)
		return NULL;

	memset(tmp->user, 0, MINIBUF_SIZE);
	memset(tmp->domain, 0, MINIBUF_SIZE);
	memset(tmp->workstation, 0, MINIBUF_SIZE);
	memset(tmp->passntlm2, 0, MINIBUF_SIZE);
	memset(tmp->passnt, 0, MINIBUF_SIZE);
	memset(tmp->passlm, 0, MINIBUF_SIZE);
	tmp->hashntlm2 = 1;
	tmp->hashnt = 0;
	tmp->hashlm = 0;
	tmp->flags = 0;

	return tmp;
}

struct auth_s *copy_auth(struct auth_s *dst, struct auth_s *src, int fullcopy) {
	dst->hashntlm2 = src->hashntlm2;
	dst->hashnt = src->hashnt;
	dst->hashlm = src->hashlm;
	dst->flags = src->flags;
#ifdef ENABLE_KERBEROS
	dst->haskrb = src->haskrb;
#endif

	strlcpy(dst->domain, src->domain, MINIBUF_SIZE);
	strlcpy(dst->workstation, src->workstation, MINIBUF_SIZE);

	if (fullcopy) {
		strlcpy(dst->user, src->user, MINIBUF_SIZE);
		if (src->passntlm2)
			memcpy(dst->passntlm2, src->passntlm2, MINIBUF_SIZE);
		if (src->passnt)
			memcpy(dst->passnt, src->passnt, MINIBUF_SIZE);
		if (src->passlm)
			memcpy(dst->passlm, src->passlm, MINIBUF_SIZE);
	} else {
		memset(dst->user, 0, MINIBUF_SIZE);
		memset(dst->passntlm2, 0, MINIBUF_SIZE);
		memset(dst->passnt, 0, MINIBUF_SIZE);
		memset(dst->passlm, 0, MINIBUF_SIZE);
	}

	return dst;
}

struct auth_s *dup_auth(struct auth_s *creds, int fullcopy) {
	struct auth_s *tmp;

	tmp = new_auth();
	if (tmp == NULL)
		return NULL;

	return copy_auth(tmp, creds, fullcopy);
}

void dump_auth(struct auth_s *creds) {
	char *tmp;

	cntlm_log(LOG_INFO, "Credentials structure dump:\n");
	if (creds == NULL) {
		cntlm_log(LOG_INFO, "Struct is not allocated!\n");
		return;
	}

	cntlm_log(LOG_INFO, "User:       %s\n", creds->user);
	cntlm_log(LOG_INFO, "Domain:     %s\n", creds->domain);
	cntlm_log(LOG_INFO, "Wks:        %s\n", creds->workstation);
	cntlm_log(LOG_INFO, "HashNTLMv2: %d\n", creds->hashntlm2);
	cntlm_log(LOG_INFO, "HashNT:     %d\n", creds->hashnt);
	cntlm_log(LOG_INFO, "HashLM:     %d\n", creds->hashlm);
	cntlm_log(LOG_INFO, "Flags:      %X\n", creds->flags);
	if (creds->passntlm2) {
		tmp = printmem(creds->passntlm2, 16, 8);
		cntlm_log(LOG_INFO, "PassNTLMv2: %s\n", tmp);
		free(tmp);
	}

	if (creds->passnt) {
		tmp = printmem(creds->passnt, 16, 8);
		cntlm_log(LOG_INFO, "PassNT:     %s\n", tmp);
		free(tmp);
	}

	if (creds->passlm) {
		tmp = printmem(creds->passlm, 16, 8);
		cntlm_log(LOG_INFO, "PassLM:     %s\n\n", tmp);
		free(tmp);
	}
}
