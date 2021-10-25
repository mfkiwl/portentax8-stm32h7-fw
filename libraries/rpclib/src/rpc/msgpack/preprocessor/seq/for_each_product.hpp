# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef MSGPACK_PREPROCESSOR_SEQ_FOR_EACH_PRODUCT_HPP
# define MSGPACK_PREPROCESSOR_SEQ_FOR_EACH_PRODUCT_HPP
#
# include <rpc/msgpack/preprocessor/arithmetic/dec.hpp>
# include <rpc/msgpack/preprocessor/config/config.hpp>
# include <rpc/msgpack/preprocessor/control/if.hpp>
# include <rpc/msgpack/preprocessor/repetition/for.hpp>
# include <rpc/msgpack/preprocessor/seq/seq.hpp>
# include <rpc/msgpack/preprocessor/seq/size.hpp>
# include <rpc/msgpack/preprocessor/tuple/elem.hpp>
# include <rpc/msgpack/preprocessor/tuple/rem.hpp>
#
# /* MSGPACK_PP_SEQ_FOR_EACH_PRODUCT */
#
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT(macro, sets) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_E(MSGPACK_PP_FOR, macro, sets)
#
# /* MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_R */
#
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_R(r, macro, sets) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_E(MSGPACK_PP_FOR_ ## r, macro, sets)
#
# if ~MSGPACK_PP_CONFIG_FLAGS() & MSGPACK_PP_CONFIG_EDG()
#    define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_E(impl, macro, sets) impl((MSGPACK_PP_SEQ_HEAD(sets)(nil), MSGPACK_PP_SEQ_TAIL(sets)(nil), (nil), macro), MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_P, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_O, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_0)
# else
#    define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_E(impl, macro, sets) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_E_I(impl, macro, sets)
#    define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_E_I(impl, macro, sets) impl((MSGPACK_PP_SEQ_HEAD(sets)(nil), MSGPACK_PP_SEQ_TAIL(sets)(nil), (nil), macro), MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_P, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_O, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_0)
# endif
#
# if MSGPACK_PP_CONFIG_FLAGS() & MSGPACK_PP_CONFIG_STRICT()
#    define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_P(r, data) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_P_I data
#    define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_P_I(cset, rset, res, macro) MSGPACK_PP_DEC(MSGPACK_PP_SEQ_SIZE(cset))
# else
#    define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_P(r, data) MSGPACK_PP_DEC(MSGPACK_PP_SEQ_SIZE(MSGPACK_PP_TUPLE_ELEM(4, 0, data)))
# endif
#
# if ~MSGPACK_PP_CONFIG_FLAGS() & MSGPACK_PP_CONFIG_MWCC()
#    define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_O(r, data) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_O_I data
#    define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_O_I(cset, rset, res, macro) (MSGPACK_PP_SEQ_TAIL(cset), rset, res, macro)
# else
#    define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_O(r, data) (MSGPACK_PP_SEQ_TAIL(MSGPACK_PP_TUPLE_ELEM(4, 0, data)), MSGPACK_PP_TUPLE_ELEM(4, 1, data), MSGPACK_PP_TUPLE_ELEM(4, 2, data), MSGPACK_PP_TUPLE_ELEM(4, 3, data))
# endif
#
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_C(data, i) MSGPACK_PP_IF(MSGPACK_PP_DEC(MSGPACK_PP_SEQ_SIZE(MSGPACK_PP_TUPLE_ELEM(4, 1, data))), MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_N_ ## i, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_I)
#
# if ~MSGPACK_PP_CONFIG_FLAGS() & MSGPACK_PP_CONFIG_EDG()
#    define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_I(r, data) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_I_I(r, MSGPACK_PP_TUPLE_ELEM(4, 0, data), MSGPACK_PP_TUPLE_ELEM(4, 1, data), MSGPACK_PP_TUPLE_ELEM(4, 2, data), MSGPACK_PP_TUPLE_ELEM(4, 3, data))
# else
#    define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_I(r, data) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_I_IM(r, MSGPACK_PP_TUPLE_REM_4 data)
#    define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_I_IM(r, im) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_I_I(r, im)
# endif
#
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_I_I(r, cset, rset, res, macro) macro(r, MSGPACK_PP_SEQ_TAIL(res (MSGPACK_PP_SEQ_HEAD(cset))))
#
# if ~MSGPACK_PP_CONFIG_FLAGS() & MSGPACK_PP_CONFIG_MWCC()
#    define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_H(data) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_H_I data
# else
#    define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_H(data) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_H_I(MSGPACK_PP_TUPLE_ELEM(4, 0, data), MSGPACK_PP_TUPLE_ELEM(4, 1, data), MSGPACK_PP_TUPLE_ELEM(4, 2, data), MSGPACK_PP_TUPLE_ELEM(4, 3, data))
# endif
#
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_H_I(cset, rset, res, macro) (MSGPACK_PP_SEQ_HEAD(rset)(nil), MSGPACK_PP_SEQ_TAIL(rset), res (MSGPACK_PP_SEQ_HEAD(cset)), macro)
#
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_0(r, data) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_C(data, 0)(r, data)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_1(r, data) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_C(data, 1)(r, data)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_2(r, data) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_C(data, 2)(r, data)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_3(r, data) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_C(data, 3)(r, data)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_4(r, data) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_C(data, 4)(r, data)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_5(r, data) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_C(data, 5)(r, data)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_6(r, data) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_C(data, 6)(r, data)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_7(r, data) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_C(data, 7)(r, data)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_8(r, data) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_C(data, 8)(r, data)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_9(r, data) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_C(data, 9)(r, data)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_10(r, data) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_C(data, 10)(r, data)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_11(r, data) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_C(data, 11)(r, data)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_12(r, data) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_C(data, 12)(r, data)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_13(r, data) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_C(data, 13)(r, data)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_14(r, data) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_C(data, 14)(r, data)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_15(r, data) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_C(data, 15)(r, data)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_16(r, data) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_C(data, 16)(r, data)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_17(r, data) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_C(data, 17)(r, data)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_18(r, data) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_C(data, 18)(r, data)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_19(r, data) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_C(data, 19)(r, data)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_20(r, data) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_C(data, 20)(r, data)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_21(r, data) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_C(data, 21)(r, data)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_22(r, data) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_C(data, 22)(r, data)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_23(r, data) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_C(data, 23)(r, data)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_24(r, data) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_C(data, 24)(r, data)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_25(r, data) MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_C(data, 25)(r, data)
#
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_N_0(r, data) MSGPACK_PP_FOR_ ## r(MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_H(data), MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_P, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_O, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_1)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_N_1(r, data) MSGPACK_PP_FOR_ ## r(MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_H(data), MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_P, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_O, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_2)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_N_2(r, data) MSGPACK_PP_FOR_ ## r(MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_H(data), MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_P, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_O, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_3)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_N_3(r, data) MSGPACK_PP_FOR_ ## r(MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_H(data), MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_P, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_O, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_4)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_N_4(r, data) MSGPACK_PP_FOR_ ## r(MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_H(data), MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_P, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_O, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_5)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_N_5(r, data) MSGPACK_PP_FOR_ ## r(MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_H(data), MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_P, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_O, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_6)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_N_6(r, data) MSGPACK_PP_FOR_ ## r(MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_H(data), MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_P, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_O, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_7)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_N_7(r, data) MSGPACK_PP_FOR_ ## r(MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_H(data), MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_P, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_O, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_8)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_N_8(r, data) MSGPACK_PP_FOR_ ## r(MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_H(data), MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_P, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_O, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_9)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_N_9(r, data) MSGPACK_PP_FOR_ ## r(MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_H(data), MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_P, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_O, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_10)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_N_10(r, data) MSGPACK_PP_FOR_ ## r(MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_H(data), MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_P, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_O, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_11)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_N_11(r, data) MSGPACK_PP_FOR_ ## r(MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_H(data), MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_P, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_O, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_12)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_N_12(r, data) MSGPACK_PP_FOR_ ## r(MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_H(data), MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_P, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_O, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_13)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_N_13(r, data) MSGPACK_PP_FOR_ ## r(MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_H(data), MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_P, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_O, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_14)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_N_14(r, data) MSGPACK_PP_FOR_ ## r(MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_H(data), MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_P, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_O, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_15)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_N_15(r, data) MSGPACK_PP_FOR_ ## r(MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_H(data), MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_P, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_O, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_16)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_N_16(r, data) MSGPACK_PP_FOR_ ## r(MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_H(data), MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_P, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_O, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_17)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_N_17(r, data) MSGPACK_PP_FOR_ ## r(MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_H(data), MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_P, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_O, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_18)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_N_18(r, data) MSGPACK_PP_FOR_ ## r(MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_H(data), MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_P, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_O, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_19)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_N_19(r, data) MSGPACK_PP_FOR_ ## r(MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_H(data), MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_P, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_O, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_20)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_N_20(r, data) MSGPACK_PP_FOR_ ## r(MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_H(data), MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_P, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_O, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_21)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_N_21(r, data) MSGPACK_PP_FOR_ ## r(MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_H(data), MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_P, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_O, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_22)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_N_22(r, data) MSGPACK_PP_FOR_ ## r(MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_H(data), MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_P, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_O, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_23)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_N_23(r, data) MSGPACK_PP_FOR_ ## r(MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_H(data), MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_P, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_O, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_24)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_N_24(r, data) MSGPACK_PP_FOR_ ## r(MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_H(data), MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_P, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_O, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_25)
# define MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_N_25(r, data) MSGPACK_PP_FOR_ ## r(MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_H(data), MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_P, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_O, MSGPACK_PP_SEQ_FOR_EACH_PRODUCT_M_26)
#
# endif
