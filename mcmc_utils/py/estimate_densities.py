import numpy as np
from scipy.stats import gamma, norm


def estimateFiniteNormalMixtureDensity(weights, atoms, xgrid):
    """
    Estimate the density of a finite mixture over a unidimensional grid
    Args:
     - weights: numpy array, the weights of the mixture
     - atoms: list of UnivariateMixtureAtom
     - xgrid: numpy array, the grid over which we want to evaluate the density
    """
    out = np.zeros(len(xgrid))
    for h, atom in enumerate(atoms):
        out += weights[h] * norm.pdf(xgrid, atom.mean, atom.stdev)
    return out


def estimateHDPNormalMixtureDensity(
        cluster_sizes, betas, atoms, p0params, alpha, xgrid):
    """
    Estimate the density of an HDP mixture over an unidimensional grid
    Args:
     - cluster_sizes: list or np.array, the sizes of the clusters for the
        population/restaurant under investigation
     - betas: np.array, the parameter beta of the direct sampler for the HDP
     - atoms: list of UnivariateMixtureAtom
     - params: an instance of NormalGammaParams
     - alpha: the total mass parameter alpha
     - xgrid: numpy array, the grid over which we want to evaluate the density
    """
    out = np.zeros(len(xgrid))
    weights = np.zeros(len(atoms))
    ntot = sum(cluster_sizes)
    for h in range(len(atoms)):
        weights[h] = cluster_sizes[h] + alpha * betas[h]

    weights /= (ntot + alpha)

    for h, atom in enumerate(atoms):
        out += weights[h] * norm.pdf(xgrid, atom.mean, atom.stdev)

    # TODO: rough approximation, still better than nothing
    tau = gamma.rvs(p0params.a, 1 / p0params.b)
    mean = norm.rvs(
        p0params.mu0, 1.0 / np.sqrt(p0params.lam * tau))
    out += alpha * betas[-1] / (ntot + alpha) * norm.pdf(
        xgrid, mean, 1.0 / np.sqrt(tau))

    return out
