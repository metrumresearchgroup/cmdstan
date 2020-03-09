#ifndef STAN_MATH_PRIM_PROB_BINOMIAL_LCDF_HPP
#define STAN_MATH_PRIM_PROB_BINOMIAL_LCDF_HPP

#include <stan/math/prim/meta.hpp>
#include <stan/math/prim/err.hpp>
#include <stan/math/prim/fun/beta.hpp>
#include <stan/math/prim/fun/constants.hpp>
#include <stan/math/prim/fun/inc_beta.hpp>
#include <stan/math/prim/fun/log.hpp>
#include <stan/math/prim/fun/max_size.hpp>
#include <stan/math/prim/fun/size.hpp>
#include <stan/math/prim/fun/size_zero.hpp>
#include <stan/math/prim/fun/value_of.hpp>
#include <cmath>

namespace stan {
namespace math {

/** \ingroup prob_dists
 * Returns the log CDF for the binomial distribution evaluated at the
 * specified success, population size, and chance of success. If given
 * containers of matching lengths, returns the log sum of probabilities.
 *
 * @tparam T_n type of successes parameter
 * @tparam T_N type of population size parameter
 * @tparam theta type of chance of success parameter
 * @param n successes parameter
 * @param N population size parameter
 * @param theta chance of success parameter
 * @return log probability or log sum of probabilities
 * @throw std::domain_error if N is negative
 * @throw std::domain_error if theta is not a valid probability
 * @throw std::invalid_argument if container sizes mismatch
 */
template <typename T_n, typename T_N, typename T_prob>
return_type_t<T_prob> binomial_lcdf(const T_n& n, const T_N& N,
                                    const T_prob& theta) {
  static const char* function = "binomial_lcdf";
  using T_partials_return = partials_return_t<T_n, T_N, T_prob>;

  if (size_zero(n, N, theta)) {
    return 0.0;
  }

  T_partials_return P(0.0);

  check_nonnegative(function, "Population size parameter", N);
  check_finite(function, "Probability parameter", theta);
  check_bounded(function, "Probability parameter", theta, 0.0, 1.0);
  check_consistent_sizes(function, "Successes variable", n,
                         "Population size parameter", N,
                         "Probability parameter", theta);

  scalar_seq_view<T_n> n_vec(n);
  scalar_seq_view<T_N> N_vec(N);
  scalar_seq_view<T_prob> theta_vec(theta);
  size_t max_size_seq_view = max_size(n, N, theta);

  using std::exp;
  using std::log;
  using std::pow;

  operands_and_partials<T_prob> ops_partials(theta);

  // Explicit return for extreme values
  // The gradients are technically ill-defined,
  // but treated as negative infinity
  for (size_t i = 0; i < stan::math::size(n); i++) {
    if (value_of(n_vec[i]) < 0) {
      return ops_partials.build(NEGATIVE_INFTY);
    }
  }

  for (size_t i = 0; i < max_size_seq_view; i++) {
    const T_partials_return n_dbl = value_of(n_vec[i]);
    const T_partials_return N_dbl = value_of(N_vec[i]);

    // Explicit results for extreme values
    // The gradients are technically ill-defined, but treated as zero
    if (n_dbl >= N_dbl) {
      continue;
    }

    const T_partials_return theta_dbl = value_of(theta_vec[i]);
    const T_partials_return Pi
        = inc_beta(N_dbl - n_dbl, n_dbl + 1, 1 - theta_dbl);

    P += log(Pi);

    if (!is_constant_all<T_prob>::value) {
      const T_partials_return denom = beta(N_dbl - n_dbl, n_dbl + 1) * Pi;
      ops_partials.edge1_.partials_[i]
          -= pow(theta_dbl, n_dbl) * pow(1 - theta_dbl, N_dbl - n_dbl - 1)
             / denom;
    }
  }
  return ops_partials.build(P);
}

}  // namespace math
}  // namespace stan
#endif