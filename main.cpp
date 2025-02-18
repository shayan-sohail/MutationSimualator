#include <iostream>
#include <chrono>
#include "utils.h"

std::random_device rd;

void initialize(std::vector<Gene>& pop)
{
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 54);
    for (auto& p : pop) std::generate(p.chromosomes.begin(), p.chromosomes.end(), [&dist, &gen]() { return dist(gen); });
}

void initialize(std::vector<Gene>& population, Gene original, std::vector<double>& dists, std::vector<Gene>& closest)
{
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 54);
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        std::generate(population[i].chromosomes.begin(), population[i].chromosomes.end(), [&dist, &gen]() { return dist(gen); });
        dists[i] = sqrt(dists[i]);
    }
    std::vector<double> sorted_dists = dists;

    sort(sorted_dists.begin(), sorted_dists.begin() + POPULATION_SIZE);

    for (int i = 0; i < MAX_POOL; i++)
    {
        closest[i] = population[std::distance(dists.begin(), std::find(dists.begin(), dists.end(), sorted_dists[i]))];
    }
}

int main()
{
    Gene original;
    std::vector<Gene> population(MAX_POPULATION_SIZE);
    std::vector<double> euc_distances(MAX_POPULATION_SIZE);
    std::vector<Gene> closest(MAX_POOL);
    srand(time(NULL));
    int iterations = 0;

    original.chromosomes = { 1, 0, 1, 2, 10, 1, 4, 5, 6, 11, 3, 7, 8, 12, 0, 4, 6, 8, 13, 1, 5, 7, 14, 0,
           2, 3, 15, 0, 4, 8, 9, 16, 1, 6, 8, 9, 17, 0, 4, 6, 9, 18, 0, 13, 9, 19, 0, 10,
           3, 20, 0, 29, 47, 21, 0, 17, 4, 22, 4, 9, 23, 0, 30, 12, 24, 4, 39, 25, 0, 49, 14, 26,
           0, 25, 4, 9, 27, 2, 21, 50, 28, 2, 43, 37, 29, 0, 11, 20, 23, 30, 4, 2, 31, 3, 39, 19,
           32, 0, 47, 38, 33, 0, 16, 25, 41, 34, 0, 26, 47, 35, 0, 27, 18, 39, 36, 0, 52, 54, 37, 2,
           46, 15, 38, 0, 3, 31, 39, 2, 16, 22, 40, 4, 6, 41, 2, 35, 50, 42, 1, 2, 3, 43, 4, 0,
           44, 4, 8, 45, 0, 32, 14, 46, 4, 1, 47, 0, 40, 39, 48, 0, 34, 40, 49, 0, 25, 1, 50, 0,
           42, 44, 51, 0, 14, 45, 52, 0, 28, 44, 53, 2, 27, 36, 54 };

    population.resize(MAX_POPULATION_SIZE);
    initialize(population, original, euc_distances, closest);
    auto now = std::chrono::system_clock::now();
    auto ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto start = ms.time_since_epoch().count();
    Utils::mutate(population, closest, Utils::combinational_crossing(population, closest));
    while (!Utils::check(original, population) && iterations < MAX_ITERATIONS)
    {
        iterations++;
        printf("Iteration: %d\n", iterations);
        Utils::get_euclidean_distances(population, original, euc_distances);
        Utils::get_closest_matches(population, closest, euc_distances, original);
        Utils::mutate(population, closest, Utils::combinational_crossing(population, closest));
    }
    now = std::chrono::system_clock::now();
    ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto end = ms.time_since_epoch().count();
    std::printf("Time taken: %2.4f s\n", (end - start) / 1000.0);
    return 0;
}