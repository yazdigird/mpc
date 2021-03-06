/* clear_parameters -- Deallocate memory for function parameters.

Copyright (C) 2012, 2013, 2014 INRIA

This file is part of GNU MPC.

GNU MPC is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the
Free Software Foundation; either version 3 of the License, or (at your
option) any later version.

GNU MPC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General Public License
along with this program. If not, see http://www.gnu.org/licenses/ .
*/

#include "mpc-tests.h"

static void
clear_param (mpc_operand_t* p, mpc_param_t t)
{
  switch (t)
    {
    case NATIVE_INT:
    case NATIVE_UL:
    case NATIVE_L:
    case NATIVE_D:
      break;

    case GMP_Z:
      mpz_clear (p->mpz);
      break;
    case GMP_Q:
      mpq_clear (p->mpq);
      break;
    case GMP_F:
      mpf_clear (p->mpf);
      break;

    case MPFR_INEX:
      break;
    case MPFR:
      mpfr_clear (p->mpfr);
      break;

    case MPC_INEX:
    case MPCC_INEX:
      break;
    case MPC:
      mpc_clear (p->mpc);
      break;

    case MPFR_RND:
    case MPC_RND:
      break;

    default:
      fprintf (stderr, "clear_parameters: unsupported type.\n");
      exit (1);
    }
}

void
clear_parameters (mpc_fun_param_t *params)
{
  int in, out;
  int total = params->nbout + params->nbin;

  free (params->name);
  for (out = 0; out < params->nbout; out++)
    {
      clear_param (&(params->P[out]), params->T[out]);
      clear_param (&(params->P[total + out]), params->T[out]);
    }

  for (in = params->nbout; in < total; in++)
    {
      clear_param (&(params->P[in]), params->T[in]);
    }
}
