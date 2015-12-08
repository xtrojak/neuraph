#include "types.h"
#include <list>
#include <vector>
#include <tuple>
#include <random>
#include <ctime>
#include <sstream>
#include <iostream>

class Polynoms
{
    public:

        Polynoms(u32 minDeg, u32 maxDeg, u32 count)
        {
            random_device.seed(std::time(nullptr));

            for (u32 i = 0; i < count; i++)
                generate(minDeg, maxDeg);
        }

        static void print(const std::vector<f64> &poly)
        {
            if (poly[0] != 0)
                std::cout << poly[0] << " + ";

            for (u32 i = 1; i < poly.size(); i++)
                if (poly[i] != 0)
                    std::cout << poly[i] << "x^" << i << " + ";

            std::cout << "\b\b\b  \n";
        }

        static const std::vector<f64> parsePoly(const std::string &line)
        {
			std::vector<f64> p;
			std::stringstream ss(line);
			std::string item;

			while (std::getline(ss, item, ' '))
			{
				try
				{
					p.push_back(std::stoi(item));
				}
				catch (std::exception &e)
				{
					std::cout << e.what() << " " << line << "\n";
					break;
				}
			}

			return p;
		}
        
        static std::vector<f64> differentiate(const std::vector<f64> &polynomial)
        {
            std::vector<f64> p;

            for (u32 i = 1; i < polynomial.size(); i++)
                p.push_back(polynomial[i] * i);

            return p;
        }

        std::list< std::tuple< std::vector<f64>, std::vector<f64> > > &getPolynoms()
        {
            return Polys;
        }


    private:
        std::list< std::tuple< std::vector<f64>, std::vector<f64> > > Polys;
        static constexpr i32 minCoeff = 0, maxCoeff = 99;

        std::mt19937 random_device;

        void generate(u32 minD, u32 maxD)
        {
            std::uniform_int_distribution<u32> degree_dis(minD, maxD);
            const u32 degree = degree_dis(random_device);

            std::vector<f64> polynomial;
            std::uniform_int_distribution<u32> coeffs_dis(minCoeff, maxCoeff);
            for (u32 i = 0; i < degree; i++)
                polynomial.push_back(coeffs_dis(random_device));

            Polys.push_back(std::make_tuple(polynomial, differentiate(polynomial)));
        }
};
