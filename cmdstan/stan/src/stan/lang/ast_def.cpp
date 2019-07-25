#ifndef STAN_LANG_AST_DEF_CPP
#define STAN_LANG_AST_DEF_CPP

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/recursive_variant.hpp>

#include <stan/lang/ast.hpp>

#include <stan/lang/ast/scope_def.hpp>
#include <stan/lang/ast/variable_map_def.hpp>

#include <stan/lang/ast/type/bare_array_type_def.hpp>
#include <stan/lang/ast/type/bare_expr_type_def.hpp>
#include <stan/lang/ast/type/block_array_type_def.hpp>
#include <stan/lang/ast/type/block_var_type_def.hpp>
#include <stan/lang/ast/type/local_array_type_def.hpp>
#include <stan/lang/ast/type/local_var_type_def.hpp>

#include <stan/lang/ast/type/cholesky_factor_corr_block_type_def.hpp>
#include <stan/lang/ast/type/cholesky_factor_cov_block_type_def.hpp>
#include <stan/lang/ast/type/corr_matrix_block_type_def.hpp>
#include <stan/lang/ast/type/cov_matrix_block_type_def.hpp>
#include <stan/lang/ast/type/double_block_type_def.hpp>
#include <stan/lang/ast/type/double_type_def.hpp>
#include <stan/lang/ast/type/ill_formed_type_def.hpp>
#include <stan/lang/ast/type/int_block_type_def.hpp>
#include <stan/lang/ast/type/int_type_def.hpp>
#include <stan/lang/ast/type/matrix_block_type_def.hpp>
#include <stan/lang/ast/type/matrix_local_type_def.hpp>
#include <stan/lang/ast/type/matrix_type_def.hpp>
#include <stan/lang/ast/type/ordered_block_type_def.hpp>
#include <stan/lang/ast/type/positive_ordered_block_type_def.hpp>
#include <stan/lang/ast/type/row_vector_block_type_def.hpp>
#include <stan/lang/ast/type/row_vector_local_type_def.hpp>
#include <stan/lang/ast/type/row_vector_type_def.hpp>
#include <stan/lang/ast/type/simplex_block_type_def.hpp>
#include <stan/lang/ast/type/unit_vector_block_type_def.hpp>
#include <stan/lang/ast/type/vector_block_type_def.hpp>
#include <stan/lang/ast/type/vector_local_type_def.hpp>
#include <stan/lang/ast/type/vector_type_def.hpp>
#include <stan/lang/ast/type/void_type_def.hpp>

#include <stan/lang/ast/fun/bare_type_is_data_vis_def.hpp>
#include <stan/lang/ast/fun/bare_type_order_id_vis_def.hpp>
#include <stan/lang/ast/fun/bare_type_set_is_data_vis_def.hpp>
#include <stan/lang/ast/fun/bare_type_total_dims_vis_def.hpp>
#include <stan/lang/ast/fun/bare_type_vis_def.hpp>
#include <stan/lang/ast/fun/block_type_bounds_vis_def.hpp>
#include <stan/lang/ast/fun/block_type_is_specialized_vis_def.hpp>
#include <stan/lang/ast/fun/block_type_offset_multiplier_vis_def.hpp>
#include <stan/lang/ast/fun/block_type_params_total_vis_def.hpp>
#include <stan/lang/ast/fun/expression_bare_type_vis_def.hpp>
#include <stan/lang/ast/fun/is_nil_def.hpp>
#include <stan/lang/ast/fun/is_nil_vis_def.hpp>
#include <stan/lang/ast/fun/var_type_arg1_vis_def.hpp>
#include <stan/lang/ast/fun/var_type_arg2_vis_def.hpp>
#include <stan/lang/ast/fun/var_type_name_vis_def.hpp>
#include <stan/lang/ast/fun/write_bare_expr_type_def.hpp>
#include <stan/lang/ast/fun/write_block_var_type_def.hpp>
#include <stan/lang/ast/fun/write_expression_vis_def.hpp>
#include <stan/lang/ast/fun/write_idx_vis_def.hpp>

#include <stan/lang/ast/fun/ends_with_def.hpp>
#include <stan/lang/ast/fun/fun_name_exists_def.hpp>
#include <stan/lang/ast/fun/get_ccdf_def.hpp>
#include <stan/lang/ast/fun/get_cdf_def.hpp>
#include <stan/lang/ast/fun/get_prob_fun_def.hpp>
#include <stan/lang/ast/fun/has_ccdf_suffix_def.hpp>
#include <stan/lang/ast/fun/has_cdf_suffix_def.hpp>
#include <stan/lang/ast/fun/has_lp_suffix_def.hpp>
#include <stan/lang/ast/fun/has_non_param_var_def.hpp>
#include <stan/lang/ast/fun/has_non_param_var_vis_def.hpp>
#include <stan/lang/ast/fun/has_prob_fun_suffix_def.hpp>
#include <stan/lang/ast/fun/has_rng_suffix_def.hpp>
#include <stan/lang/ast/fun/has_var_def.hpp>
#include <stan/lang/ast/fun/has_var_vis_def.hpp>
#include <stan/lang/ast/fun/indexed_type_def.hpp>
#include <stan/lang/ast/fun/infer_type_indexing_def.hpp>
#include <stan/lang/ast/fun/is_assignable_def.hpp>
#include <stan/lang/ast/fun/is_multi_index_def.hpp>
#include <stan/lang/ast/fun/is_multi_index_vis_def.hpp>
#include <stan/lang/ast/fun/is_no_op_statement_vis_def.hpp>
#include <stan/lang/ast/fun/is_nonempty_def.hpp>
#include <stan/lang/ast/fun/is_space_def.hpp>
#include <stan/lang/ast/fun/is_user_defined_def.hpp>
#include <stan/lang/ast/fun/is_user_defined_prob_function_def.hpp>
#include <stan/lang/ast/fun/num_index_op_dims_def.hpp>
#include <stan/lang/ast/fun/print_scope_def.hpp>
#include <stan/lang/ast/fun/promote_primitive_def.hpp>
#include <stan/lang/ast/fun/returns_type_def.hpp>
#include <stan/lang/ast/fun/returns_type_vis_def.hpp>
#include <stan/lang/ast/fun/strip_ccdf_suffix_def.hpp>
#include <stan/lang/ast/fun/strip_cdf_suffix_def.hpp>
#include <stan/lang/ast/fun/strip_prob_fun_suffix_def.hpp>
#include <stan/lang/ast/fun/var_occurs_vis_def.hpp>

#include <stan/lang/ast/sigs/function_signatures_def.hpp>

#include <stan/lang/ast/node/block_var_decl_def.hpp>
#include <stan/lang/ast/node/local_var_decl_def.hpp>

#include <stan/lang/ast/node/var_decl_def.hpp>

#include <stan/lang/ast/node/algebra_solver_control_def.hpp>
#include <stan/lang/ast/node/algebra_solver_def.hpp>
#include <stan/lang/ast/node/array_expr_def.hpp>
#include <stan/lang/ast/node/assgn_def.hpp>
#include <stan/lang/ast/node/binary_op_def.hpp>
#include <stan/lang/ast/node/break_continue_statement_def.hpp>
#include <stan/lang/ast/node/conditional_op_def.hpp>
#include <stan/lang/ast/node/conditional_statement_def.hpp>
#include <stan/lang/ast/node/double_literal_def.hpp>
#include <stan/lang/ast/node/expression_def.hpp>
#include <stan/lang/ast/node/for_array_statement_def.hpp>
#include <stan/lang/ast/node/for_matrix_statement_def.hpp>
#include <stan/lang/ast/node/for_statement_def.hpp>
#include <stan/lang/ast/node/fun_def.hpp>
#include <stan/lang/ast/node/function_decl_def_def.hpp>
#include <stan/lang/ast/node/function_decl_defs_def.hpp>
#include <stan/lang/ast/node/idx_def.hpp>
#include <stan/lang/ast/node/increment_log_prob_statement_def.hpp>
#include <stan/lang/ast/node/index_op_def.hpp>
#include <stan/lang/ast/node/index_op_sliced_def.hpp>
#include <stan/lang/ast/node/int_literal_def.hpp>
#include <stan/lang/ast/node/integrate_1d_def.hpp>
#include <stan/lang/ast/node/integrate_ode_control_def.hpp>
#include <stan/lang/ast/node/integrate_ode_def.hpp>
#include <stan/lang/ast/node/lb_idx_def.hpp>
#include <stan/lang/ast/node/lub_idx_def.hpp>
#include <stan/lang/ast/node/map_rect_def.hpp>
#include <stan/lang/ast/node/matrix_expr_def.hpp>
#include <stan/lang/ast/node/multi_idx_def.hpp>
#include <stan/lang/ast/node/offset_multiplier_def.hpp>
#include <stan/lang/ast/node/omni_idx_def.hpp>
#include <stan/lang/ast/node/print_statement_def.hpp>
#include <stan/lang/ast/node/printable_def.hpp>
#include <stan/lang/ast/node/program_def.hpp>
#include <stan/lang/ast/node/range_def.hpp>
#include <stan/lang/ast/node/reject_statement_def.hpp>
#include <stan/lang/ast/node/return_statement_def.hpp>
#include <stan/lang/ast/node/row_vector_expr_def.hpp>
#include <stan/lang/ast/node/sample_def.hpp>
#include <stan/lang/ast/node/statement_def.hpp>
#include <stan/lang/ast/node/statements_def.hpp>
#include <stan/lang/ast/node/ub_idx_def.hpp>
#include <stan/lang/ast/node/unary_op_def.hpp>
#include <stan/lang/ast/node/uni_idx_def.hpp>
#include <stan/lang/ast/node/variable_def.hpp>
#include <stan/lang/ast/node/variable_dims_def.hpp>
#include <stan/lang/ast/node/while_statement_def.hpp>

// Torsten
#include <stan/torsten/torsten_ast_def.hpp>


// Torsten
#include <stan/torsten/torsten_ast_def.hpp>


#endif