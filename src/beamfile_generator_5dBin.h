#ifndef ANTOK_BEAMFILE_GENERATOR_5DBIN_H
#define ANTOK_BEAMFILE_GENERATOR_5DBIN_H

#include<iostream>
#include<vector>
#include<set>

#include<boost/shared_ptr.hpp>
#include<boost/enable_shared_from_this.hpp>


namespace antok {

	namespace beamfileGenerator {

		class fiveDimCoord;

		class fiveDimBin : public boost::enable_shared_from_this<fiveDimBin> {

		  public:

			fiveDimBin()
				: _a(5,0.),
				  _b(5,0.),
				  _entries(0),
				  _neighbors(),
				  _onLowerEdge(5, false),
				  _onUpperEdge(5, false),
				  _sigmaCache(),
				  _sigmaCalculationMethodCache(-1) { _nExistingBins += 1; }

			// this takes ownership of entries!
			fiveDimBin(double a0, double a1, double a2, double a3, double a4,
					   double b0, double b1, double b2, double b3, double b4,
					   std::vector<antok::beamfileGenerator::fiveDimCoord*>* entries);

			// this takes ownership of entries!
			fiveDimBin(const std::vector<double>& a,
			           const std::vector<double>& b,
			           std::vector<antok::beamfileGenerator::fiveDimCoord*>* entries);

			virtual ~fiveDimBin();

			void set(const std::vector<double>& a, const std::vector<double>& b);

			const std::vector<double>& getLowerCorner() const { return _a; }
			const std::vector<double>& getUpperCorner() const { return _b; }

			bool inBin(const std::vector<double>& x) const;

			std::pair<boost::shared_ptr<antok::beamfileGenerator::fiveDimBin>,
			          boost::shared_ptr<antok::beamfileGenerator::fiveDimBin> > divide(const int& dim,
			                                                                           std::stringstream* outPtr = 0,
			                                                                           unsigned int depth = 0) const;

			bool areWeNeighbors(boost::shared_ptr<const antok::beamfileGenerator::fiveDimBin> bin) const;
			void addNeighbor(boost::shared_ptr<antok::beamfileGenerator::fiveDimBin> bin) { _neighbors.insert(bin); }
			void removeNeighbor(boost::shared_ptr<const antok::beamfileGenerator::fiveDimBin> bin);
			const std::set<boost::shared_ptr<antok::beamfileGenerator::fiveDimBin> >& getNeighbors() const { return _neighbors; }

			void setOnLowerEdge(const std::vector<bool>& onLowerEdge) { _onLowerEdge = onLowerEdge; }
			void setOnUpperEdge(const std::vector<bool>& onUpperEdge) { _onUpperEdge = onUpperEdge; }
			const std::vector<bool>& getOnLowerEdge() const { return _onLowerEdge; }
			const std::vector<bool>& getOnUpperEdge() const { return _onUpperEdge; }
			std::vector<bool>& getOnLowerEdge() { return _onLowerEdge; }
			std::vector<bool>& getOnUpperEdge() { return _onUpperEdge; }

			double getVolume() const;
			const std::vector<antok::beamfileGenerator::fiveDimCoord*>* getEvents() const { return _entries; }
			unsigned int getEntries() const { return _entries->size(); }
			unsigned int getEdgeity() const;

			const boost::shared_ptr<const std::vector<std::vector<double> > > getSigmas(bool forceCalculation = false) const;
			const int& getSigmaCalculationMethod() const { return _sigmaCalculationMethodCache; };
			void clearSigmaCache() const { _sigmaCache.reset(); }

			std::ostream& print(std::ostream& out, unsigned int indent = 0) const;

			static const long& getNExistingBins() { return _nExistingBins; }

			static void setDebug(bool debug = true) { _debug = debug; }
			static void setPrintNeighbors(bool printNeighbors = true) { _printNeighbors = printNeighbors; }
			static void setDifferentSigmaCalculationForEdges(bool setDiffSigmaCalc = true) { _differentSigmaCalculationForEdges = setDiffSigmaCalc; }

		  private:

			std::vector<double> _a; // lower corner
			std::vector<double> _b; // upper corner

			std::vector<antok::beamfileGenerator::fiveDimCoord*>* _entries;

			std::set<boost::shared_ptr<antok::beamfileGenerator::fiveDimBin> > _neighbors;
			std::vector<bool> _onLowerEdge;
			std::vector<bool> _onUpperEdge;

			mutable boost::shared_ptr<std::vector<std::vector<double> > > _sigmaCache;
			mutable int _sigmaCalculationMethodCache;

			static const double EPSILON;
			static bool doubleEqual(const double& lhs, const double& rhs);

			static long _nExistingBins;

			static bool _debug;
			static bool _printNeighbors;
			static bool _differentSigmaCalculationForEdges;

		};

	}

}

#endif
