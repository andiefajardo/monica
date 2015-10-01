/**
Authors: 
Dr. Claas Nendel <claas.nendel@zalf.de>
Xenia Specka <xenia.specka@zalf.de>
Michael Berg <michael.berg@zalf.de>

Maintainers: 
Currently maintained by the authors.

This file is part of the MONICA model. 
Copyright (C) 2007-2013, Leibniz Centre for Agricultural Landscape Research (ZALF)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MONICA_PARAMETERS_H_
#define MONICA_PARAMETERS_H_

/**
 * @file monica-parameters.h
 */

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <functional>

#include "json11/json11.hpp"

#include "climate/climate-common.h"
#include "tools/date.h"
#include "tools/json11-helper.h"
#include "soil/soil.h"
#include "monica-typedefs.h"

namespace Monica
{
//#undef min
//#undef max

	class CentralParameterProvider;

	enum Eva2_Nutzung
	{
		NUTZUNG_UNDEFINED=0,
		NUTZUNG_GANZPFLANZE=1,
		NUTZUNG_KORN=2,
		NUTZUNG_GRUENDUENGUNG=7,
		NUTZUNG_CCM=8
	};

	const double UNDEFINED = -9999.9;
	const int UNDEFINED_INT = -9999;

	enum { MONTH=12 };

	//----------------------------------------------------------------------------

  enum ResultId
	{
		//! primary yield for the crop (e.g. the actual fruit)
		primaryYield,

		//! secondary yield for the crop (e.g. leafs and other stuff useable)
		secondaryYield,

		//! above ground biomass of the crop
		aboveGroundBiomass,

		//! Julian day of anthesis of the crop
		anthesisDay,

		//! Julian day of maturity of the crop
		maturityDay,
		
		//! Julian day of harvest
		harvestDay,

		//! sum of applied fertilizer for that crop during growth period
		sumFertiliser,

		//! sum of used irrigation water for the crop during growth period
		sumIrrigation,

		//! sum of N turnover
		sumMineralisation,

		//! the monthly average of the average corg content in the first 10 cm soil
		avg10cmMonthlyAvgCorg,

		//! the monthly average of the average corg content in the first 30 cm soil
		avg30cmMonthlyAvgCorg,

		//! the monthly average of the summed up water content in the first 90 cm soil
		mean90cmMonthlyAvgWaterContent,

		//! at some day in the year the sum of the N content in the first 90cm soil
		sum90cmYearlyNatDay,

		//! the monthly summed up amount of ground water recharge
		monthlySumGroundWaterRecharge,

		//! the monthly sum of N leaching
		monthlySumNLeaching,

		//! height of crop at harvesting date
		cropHeight,

		//! sum of NO3 content in the first 90cm soil at a special, hardcoded date
		sum90cmYearlyNO3AtDay,

		//! sum of NH4 content in the first 90cm soil at a special, hardcoded date
		sum90cmYearlyNH4AtDay,

		//! value of maximal snow depth during simulation duration
		maxSnowDepth,

		//! sum of snow depth for every day
		sumSnowDepth,

		//! sum of frost depth
		sumFrostDepth,

		//! Average soil temperature in the first 30cm soil at special, hardcoded date
		avg30cmSoilTemperature,

		//! Sum of soil temperature in the first 30cm soil at special, hardcoded date
		sum30cmSoilTemperature,

		//! Average soilmoisture content in first 30cm soil at special, hardcoded date
		avg0_30cmSoilMoisture,

		//! Average soilmoisture content in 30-60cm soil at special, hardcoded date
		avg30_60cmSoilMoisture,

		//! Average soilmoisture content in 60-90cm soil at special, hardcoded date
		avg60_90cmSoilMoisture,

		//! Average soilmoisture content in 0-90cm soil at special, hardcoded date
		avg0_90cmSoilMoisture,

		//! soilmoisture content in 0-90cm soil at special at harvest
		soilMoist0_90cmAtHarvest,

		//! corg content in the first 30 cm soil at harvest
		corg0_30cmAtHarvest,

		//! Nmin content in the first 90 cm soil at harvest
		nmin0_90cmAtHarvest,

		//! water flux at bottom layer of soil at special, hardcoded date
		waterFluxAtLowerBoundary,

		//! capillary rise in first 30 cm soil at special date
		avg0_30cmCapillaryRise,

		//! capillary rise in 30-60 cm soil at special date
		avg30_60cmCapillaryRise,

		//! capillary rise in 60-90cm cm soil at special date
		avg60_90cmCapillaryRise,

		//! percolation ratein first 30 cm soil at special date
		avg0_30cmPercolationRate,

		//! percolation ratein 30-60 cm soil at special date
		avg30_60cmPercolationRate,

		//! percolation rate in 60-90cm cm soil at special date
		avg60_90cmPercolationRate,

		//! sum of surface run off volumes during hole simulation duration
		sumSurfaceRunOff,

		//! Evapotranspiration amount at a special date
		evapotranspiration,

		//! Transpiration amount at a special date
		transpiration,

		//! Evaporation amount at a special date
		evaporation,

		//! N content in biomass after harvest
		biomassNContent,

		//! N content in above ground biomass after harvest
		aboveBiomassNContent,

		//! sum of total N uptake of plant
		sumTotalNUptake,

		//! sum of CO2 evolution rate in first 30 cm soil at special date
		sum30cmSMB_CO2EvolutionRate,

		//! volatilised NH3 at a special date
		NH3Volatilised,

		//! sum of all volatilised NH3
		sumNH3Volatilised,

		//! sum of denitrification rate in first 30cm at a special date
		sum30cmActDenitrificationRate,

		//! leaching N at boundary at special date
		leachingNAtBoundary,

		//! leaching N accumulated for a year
		yearlySumNLeaching,

		//! Groundwater recharge accumulated for a year
		yearlySumGroundWaterRecharge,

		//! Evapotranspiration in time of crop cultivation
		sumETaPerCrop,
		sumTraPerCrop,
		cropname,
		primaryYieldTM,
		secondaryYieldTM,
		monthlySurfaceRunoff,
		monthlyPrecip,
		monthlyETa,
		monthlySoilMoistureL0,
		monthlySoilMoistureL1,
		monthlySoilMoistureL2,
		monthlySoilMoistureL3,
		monthlySoilMoistureL4,
		monthlySoilMoistureL5,
		monthlySoilMoistureL6,
		monthlySoilMoistureL7,
		monthlySoilMoistureL8,
		monthlySoilMoistureL9,
		monthlySoilMoistureL10,
		monthlySoilMoistureL11,
		monthlySoilMoistureL12,
		monthlySoilMoistureL13,
		monthlySoilMoistureL14,
		monthlySoilMoistureL15,
		monthlySoilMoistureL16,
		monthlySoilMoistureL17,
		monthlySoilMoistureL18,
		daysWithCrop,
		NStress,
		WaterStress,
		HeatStress,
		OxygenStress,
		dev_stage,

		// Daily outputs used for time-dependant sensitivity analysis

		//! soilmoisture content in 0-90cm soil
		soilMoist0_90cm,

		//! corg content in the first 30 cm soil 
		corg0_30cm,

		//! Nmin content in the first 90 cm soil
		nmin0_90cm,

    //! evapotranspiration
		ETa,

		dailyAGB,

		dailyAGB_N
	};

  //! @return list of results from a single crop
	std::vector<ResultId> cropResultIds();

  std::pair<std::string, std::string> nameAndUnitForResultId(ResultId rid);

	std::vector<int> eva2CropResultIds();
	std::vector<int> eva2MonthlyResultIds();

  //! @return list of the montly results
	std::vector<ResultId> monthlyResultIds();

  //! @return list of ids used for sensitivity analysis
	std::vector<int> CCGermanyResultIds();

  struct ResultIdInfo
  {
    ResultIdInfo(const std::string& n,
                 const std::string& u,
                 const std::string& sn = std::string())
      : name(n),
        unit(u),
        shortName(sn)
    {}

    std::string name;
		std::string unit;
		std::string shortName;
	};

	ResultIdInfo resultIdInfo(ResultId rid);

	/**
	 * @brief structure holding the results for a particular crop (in one year usually)
	 */
	struct PVResult
	{
    PVResult() {}

    PVResult(int id) : id(id) {}

    PVResult(json11::Json object);

    json11::Json to_json() const;

		//! id of crop
    CropId id{-1};

		//custom id to enable mapping of monica results to user defined other entities
		//e.g. a crop activity id from Carbiocial
    int customId{-1};
    Tools::Date date;

		//! different results for a particular crop
		std::map<ResultId, double> pvResults;
	};

  typedef std::shared_ptr<PVResult> PVResultPtr;

	//----------------------------------------------------------------------------

	/**
	 * @brief
	 */
	struct YieldComponent
	{
    YieldComponent(int organId, double yieldPercentage, double yieldDryMatter);

    YieldComponent(json11::Json object);

    json11::Json to_json() const;

    std::string toString() const { return to_json().dump(); }

    int organId{-1};
    double yieldPercentage{0.0};
    double yieldDryMatter{0.0};
	};

	//----------------------------------------------------------------------------

	/**
	 * @brief Parameter for crops
	 */
	struct CropParameters
	{
    CropParameters() {}

    CropParameters(json11::Json object);

		json11::Json to_json() const;
		
		std::string toString() const;

    void resizeStageOrganVectors();

		//		pc_DevelopmentAccelerationByNitrogenStress(0)

		// members
    std::string pc_CropName;
    bool pc_Perennial{false};
    int pc_NumberOfDevelopmentalStages{0};
    int pc_NumberOfOrgans{0};
    int pc_CarboxylationPathway{0};
    double pc_DefaultRadiationUseEfficiency{0.0};
    double pc_PartBiologicalNFixation{0.0};
    double pc_InitialKcFactor{0.0};
    double pc_LuxuryNCoeff{0.0};
    double pc_MaxAssimilationRate{0.0};
    double pc_MaxCropDiameter{0.0};
    double pc_MaxCropHeight{0.0};
    double pc_CropHeightP1{0.0};
    double pc_CropHeightP2{0.0};
    double pc_StageAtMaxHeight{0.0};
    double pc_StageAtMaxDiameter{0.0};
    double pc_MinimumNConcentration{0.0};
    double pc_MinimumTemperatureForAssimilation{0.0};
    double pc_NConcentrationAbovegroundBiomass{0.0};
    double pc_NConcentrationB0{0.0};
    double pc_NConcentrationPN{0.0};
    double pc_NConcentrationRoot{0.0};
    double pc_ResidueNRatio{0.0};
    int pc_DevelopmentAccelerationByNitrogenStress{0};
    double pc_FieldConditionModifier{1.0};
    double pc_AssimilateReallocation{0.0};
    double pc_LT50cultivar{0.0};
    double pc_FrostHardening{0.0};
    double pc_FrostDehardening{0.0};
    double pc_LowTemperatureExposure{0.0};
    double pc_RespiratoryStress{0.0};
    int pc_LatestHarvestDoy{-1};

    std::vector<std::vector<double>> pc_AssimilatePartitioningCoeff;
    std::vector<std::vector<double>> pc_OrganSenescenceRate;

    std::vector<double> pc_BaseDaylength;
    std::vector<double> pc_BaseTemperature;
    std::vector<double> pc_OptimumTemperature;
    std::vector<double> pc_DaylengthRequirement;
    std::vector<double> pc_DroughtStressThreshold;
    std::vector<double> pc_OrganMaintenanceRespiration;
    std::vector<double> pc_OrganGrowthRespiration;
    std::vector<double> pc_SpecificLeafArea;
    std::vector<double> pc_StageMaxRootNConcentration;
    std::vector<double> pc_StageKcFactor;
    std::vector<double> pc_StageTemperatureSum;
    std::vector<double> pc_VernalisationRequirement;
    std::vector<double> pc_InitialOrganBiomass;
    std::vector<double> pc_CriticalOxygenContent;

    double pc_CropSpecificMaxRootingDepth{0.0};
    std::vector<int> pc_AbovegroundOrgan;
    std::vector<int> pc_StorageOrgan;

    double pc_SamplingDepth{0.0};
    double pc_TargetNSamplingDepth{0.0};
    double pc_TargetN30{0.0};
    double pc_HeatSumIrrigationStart{0.0};
    double pc_HeatSumIrrigationEnd{0.0};
    double pc_MaxNUptakeParam{0.0};
    double pc_RootDistributionParam{0.0};
    double pc_PlantDensity{0.0};
    double pc_RootGrowthLag{0.0};
    double pc_MinimumTemperatureRootGrowth{0.0};
    double pc_InitialRootingDepth{0.0};
    double pc_RootPenetrationRate{0.0};
    double pc_RootFormFactor{0.0};
    double pc_SpecificRootLength{0.0};
    int pc_StageAfterCut{0};
    double pc_CriticalTemperatureHeatStress{0.0};
    double pc_LimitingTemperatureHeatStress{0.0};
    double pc_BeginSensitivePhaseHeatStress{0.0};
    double pc_EndSensitivePhaseHeatStress{0.0};
    int pc_CuttingDelayDays{0};
    double pc_DroughtImpactOnFertilityFactor{0.0};

		std::vector<YieldComponent> pc_OrganIdsForPrimaryYield;
		std::vector<YieldComponent> pc_OrganIdsForSecondaryYield;
		std::vector<YieldComponent> pc_OrganIdsForCutting;
	};

  typedef std::shared_ptr<CropParameters> CropParametersPtr;

	//----------------------------------------------------------------------------

  enum FertiliserType { mineral, organic, undefined };

  /**
   * @brief Parameters for mineral fertiliser.
   * Simple data structure that holds information about mineral fertiliser.
   * @author Xenia Holtmann, Dr. Claas Nendel
   */
  class MineralFertiliserParameters
  {
  public:
    MineralFertiliserParameters() {}

    MineralFertiliserParameters(json11::Json object);

    MineralFertiliserParameters(const std::string& id,
                                const std::string& name,
                                double carbamid,
                                double no3,
                                double nh4);

    json11::Json to_json() const;

    std::string toString() const { return to_json().dump(); }

		std::string getId() const { return id; }
		void setId(const std::string& id) { this->id = id; }

    inline std::string getName() const { return name; }
    inline void setName(const std::string& name) { this->name = name; }

    //! @brief Returns carbamid part in percentage of fertiliser.
    //! @return Carbamid in percent
    inline double getCarbamid() const { return vo_Carbamid; }

    //! Sets carbamid part of fertilisers
    //! @param vo_Carbamid percent
    inline void setCarbamid(double carbamid) { vo_Carbamid = carbamid; }


    /**
     * @brief Returns ammonium part of fertliser.
     * @return Ammonium in percent
     */
    inline double getNH4() const { return vo_NH4; }

    /**
     * @brief Returns nitrat part of fertiliser
     * @return Nitrat in percent
     */
    inline double getNO3() const { return vo_NO3; }



    /**
     * @brief Sets nitrat part of fertiliser.
     * @param vo_NH4
     */
    inline void setNH4(double NH4) { vo_NH4 = NH4; }

    /**
     * @brief Sets nitrat part of fertiliser.
     * @param vo_NO3
     */
    inline void setNO3(double NO3) { vo_NO3 = NO3; }

  private:
    std::string id;
    std::string name;
    double vo_Carbamid{0.0};
    double vo_NH4{0.0};
    double vo_NO3{0.0};
  };

  //----------------------------------------------------------------------------

  struct NMinUserParameters
  {
    NMinUserParameters() {}

    NMinUserParameters(double min, double max, int delayInDays);

    NMinUserParameters(json11::Json object);

    json11::Json to_json() const;

    std::string toString() const { return to_json().dump(); }

    double min{0.0};
    double max{0.0};
    int delayInDays{0};
  };

  //----------------------------------------------------------------------------

  struct IrrigationParameters
  {
    IrrigationParameters() {}

    IrrigationParameters(double nitrateConcentration, double sulfateConcentration);

    IrrigationParameters(json11::Json object);

    virtual json11::Json to_json() const;

    std::string toString() const { return to_json().dump(); }

    double nitrateConcentration{0.0};
    double sulfateConcentration{0.0};
  };

  //----------------------------------------------------------------------------

  struct AutomaticIrrigationParameters : public IrrigationParameters
  {
    AutomaticIrrigationParameters() {}

    AutomaticIrrigationParameters(double a, double t, double nc, double sc);

    AutomaticIrrigationParameters(json11::Json object);

    virtual json11::Json to_json() const;

    std::string toString() const { return to_json().dump(); }

    double amount{17.0};
    double treshold{0.35};
  };

  //----------------------------------------------------------------------------

  class MeasuredGroundwaterTableInformation
  {
  public:
    MeasuredGroundwaterTableInformation() {}

    MeasuredGroundwaterTableInformation(json11::Json object);

    json11::Json to_json() const;

    std::string toString() const { return to_json().dump(); }

    void readInGroundwaterInformation(std::string path);

    double getGroundwaterInformation(Tools::Date gwDate) const;

    bool isGroundwaterInformationAvailable() const { return groundwaterInformationAvailable; }

  private:
      bool groundwaterInformationAvailable{false};
      std::map<Tools::Date, double> groundwaterInfo;
  };

  //----------------------------------------------------------------------------

	struct GeneralParameters
	{
    GeneralParameters(double layerThickness = 0.1);

    GeneralParameters(json11::Json j);

    json11::Json to_json() const;

    std::string toString() const { return to_json().dump(); }

    size_t ps_NumberOfLayers() const { return ps_LayerThickness.size(); }

    double ps_ProfileDepth{2.0};
    double ps_MaxMineralisationDepth{0.4};
    bool pc_NitrogenResponseOn{true};
    bool pc_WaterDeficitResponseOn{true};
    bool pc_EmergenceFloodingControlOn{true};
    bool pc_EmergenceMoistureControlOn{true};

    std::vector<double> ps_LayerThickness;

    bool useNMinMineralFertilisingMethod{false};
    MineralFertiliserParameters nMinFertiliserPartition;
    NMinUserParameters nMinUserParams;
    double atmosphericCO2{-1.0};
    bool useAutomaticIrrigation{false};
    AutomaticIrrigationParameters autoIrrigationParams;
    bool useSecondaryYields{true};
    double windSpeedHeight{0};
    double albedo{0};
    MeasuredGroundwaterTableInformation groundwaterInformation;

    std::string pathToOutputDir;
	};

	//----------------------------------------------------------------------------

	/**
	 * @author Claas Nendel, Michael Berg
	 */
	struct SiteParameters
	{
    SiteParameters(){}

    SiteParameters(json11::Json object);

    json11::Json to_json() const;

    std::string toString() const { return to_json().dump(); }

    double vs_Latitude{60.0};
    //! slope [m m-1]
    double vs_Slope{0.01};
    //! [m]
    double vs_HeightNN{50.0};
    //! [m]
    double vs_GroundwaterDepth{70.0};
    double vs_Soil_CN_Ratio{10.0};
    double vs_DrainageCoeff{1.0};
    double vq_NDeposition{30.0};
    double vs_MaxEffectiveRootingDepth{2.0};
	};

	//----------------------------------------------------------------------------

	/**
	* @brief Data structure that containts all relevant parameters for the automatic yield trigger.
	*/
	class AutomaticHarvestParameters
	{
  public:
    //! Enumeration for defining automatic harvesting times

    //! Definition of different harvest time definition for the automatic
    //! yield trigger
    enum HarvestTime
    {
      maturity,	//!< crop is harvested when maturity is reached
      unknown		//!< default error value
    };
		public:
    AutomaticHarvestParameters() {}
	
    AutomaticHarvestParameters(HarvestTime yt);

    AutomaticHarvestParameters(json11::Json object);

    json11::Json to_json() const;

    std::string toString() const;

    //! Setter for automatic harvest time
    void setHarvestTime(HarvestTime time) { _harvestTime = time; }

    //! Getter for automatic harvest time
    HarvestTime getHarvestTime() const { return _harvestTime; }

    //! Setter for fallback automatic harvest day
    void setLatestHarvestDOY(int doy) { _latestHarvestDOY = doy; }

    //! Getter for fallback automatic harvest day
		int getLatestHarvestDOY() const { return _latestHarvestDOY; }
		
  private:
    HarvestTime _harvestTime{unknown}; //!< Harvest time parameter
    int _latestHarvestDOY{-1}; //!< Fallback day for latest harvest of the crop
	};

	//----------------------------------------------------------------------------

	struct NMinCropParameters
	{
    NMinCropParameters() {}

    NMinCropParameters(double samplingDepth, double nTarget, double nTarget30);

    NMinCropParameters(json11::Json object);

    json11::Json to_json() const;

    std::string toString() const { return to_json().dump(); }

    double samplingDepth{0.0};
    double nTarget{0.0};
    double nTarget30{0.0};
	};

	//----------------------------------------------------------------------------

  struct OrganicMatterParameters
  {
    OrganicMatterParameters() {}

    OrganicMatterParameters(json11::Json object);

    json11::Json to_json() const;

    std::string toString() const { return to_json().dump(); }

    std::string id;
    std::string name;

    double vo_AOM_DryMatterContent{0.0}; //!< Dry matter content of added organic matter [kg DM kg FM-1]
    double vo_AOM_NH4Content{0.0}; //!< Ammonium content in added organic matter [kg N kg DM-1]
    double vo_AOM_NO3Content{0.0}; //!< Nitrate content in added organic matter [kg N kg DM-1]
    double vo_AOM_CarbamidContent{0.0}; //!< Carbamide content in added organic matter [kg N kg DM-1]

    double vo_AOM_SlowDecCoeffStandard{0.0}; //!< Decomposition rate coefficient of slow AOM at standard conditions [d-1]
    double vo_AOM_FastDecCoeffStandard{0.0}; //!< Decomposition rate coefficient of fast AOM at standard conditions [d-1]

    double vo_PartAOM_to_AOM_Slow{0.0}; //!< Part of AOM that is assigned to the slowly decomposing pool [kg kg-1
    double vo_PartAOM_to_AOM_Fast{0.0}; //!< Part of AOM that is assigned to the rapidly decomposing pool [kg kg-1]

    double vo_CN_Ratio_AOM_Slow{0.0}; //!< C to N ratio of the slowly decomposing AOM pool []
    double vo_CN_Ratio_AOM_Fast{0.0}; //!< C to N ratio of the rapidly decomposing AOM pool []

    double vo_PartAOM_Slow_to_SMB_Slow{0.0}; //!< Part of AOM slow consumed by slow soil microbial biomass [kg kg-1]
    double vo_PartAOM_Slow_to_SMB_Fast{0.0}; //!< Part of AOM slow consumed by fast soil microbial biomass [kg kg-1]

    double vo_NConcentration{0.0};
  };

  typedef OrganicMatterParameters OMP;
  typedef std::shared_ptr<OMP> OMPPtr;
  typedef std::shared_ptr<OrganicMatterParameters> OrganicMatterParametersPtr;

  //----------------------------------------------------------------------------

	/**
	 * Class that holds information of crop defined by user.
	 * @author Xenia Specka
	 */
  struct UserCropParameters
	{
    UserCropParameters() {}

    UserCropParameters(json11::Json object);

    json11::Json to_json() const;

    std::string toString() const { return to_json().dump(); }

    double pc_CanopyReflectionCoefficient{0.0};
    double pc_ReferenceMaxAssimilationRate{0.0};
    double pc_ReferenceLeafAreaIndex{0.0};
    double pc_MaintenanceRespirationParameter1{0.0};
    double pc_MaintenanceRespirationParameter2{0.0};
    double pc_MinimumNConcentrationRoot{0.0};
    double pc_MinimumAvailableN{0.0};
    double pc_ReferenceAlbedo{0.0};
    double pc_StomataConductanceAlpha{0.0};
    double pc_SaturationBeta{0.0};
    double pc_GrowthRespirationRedux{0.0};
    double pc_MaxCropNDemand{0.0};
    double pc_GrowthRespirationParameter1{0.0};
    double pc_GrowthRespirationParameter2{0.0};
    double pc_Tortuosity{0.0};
	};

	//----------------------------------------------------------------------------

	/**
	 * Class that holds information about user defined environment parameters.
	 * @author Xenia Specka
	 */
  struct UserEnvironmentParameters
	{
    UserEnvironmentParameters(){}

    UserEnvironmentParameters(json11::Json object);

    json11::Json to_json() const;

    std::string toString() const { return to_json().dump(); }

    bool p_UseAutomaticIrrigation{false};
    bool p_UseNMinMineralFertilisingMethod{false};
    bool p_UseSecondaryYields{true};
    bool p_UseAutomaticHarvestTrigger{false};

    double p_LayerThickness{0.0};
    double p_Albedo{0.0};
    double p_AthmosphericCO2{0.0};
    double p_WindSpeedHeight{0.0};
    double p_LeachingDepth{0.0};
    double p_timeStep{0.0};
    double p_MaxGroundwaterDepth{20.0};
    double p_MinGroundwaterDepth{20.0};

    int p_NumberOfLayers{0};
    int p_StartPVIndex{0};
    int p_JulianDayAutomaticFertilising{0};
    int p_MinGroundwaterDepthMonth{0};
	};

  //----------------------------------------------------------------------------

  struct UserInitialValues
	{
    UserInitialValues(){}

    UserInitialValues(json11::Json object);

    json11::Json to_json() const;

    std::string toString() const { return to_json().dump(); }

    double p_initPercentageFC{0.8}; //!< Initial soil moisture content in percent field capacity
    double p_initSoilNitrate{0.0001}; //!< Initial soil nitrate content [kg NO3-N m-3]
    double p_initSoilAmmonium{0.0001}; //!< Initial soil ammonium content [kg NH4-N m-3]
	};

	//----------------------------------------------------------------------------

	/**
	 * Class that holds information about user defined soil moisture parameters.
	 * @author Xenia Specka
	 */
  struct UserSoilMoistureParameters
	{
    UserSoilMoistureParameters(){}

    UserSoilMoistureParameters(json11::Json object);

    json11::Json to_json() const;

    std::string toString() const { return to_json().dump(); }

    std::function<double(std::string, int)> getCapillaryRiseRate;

    double pm_CriticalMoistureDepth{0.0};
    double pm_SaturatedHydraulicConductivity{0.0};
    double pm_SurfaceRoughness{0.0};
    double pm_GroundwaterDischarge{0.0};
    double pm_HydraulicConductivityRedux{0.0};
    double pm_SnowAccumulationTresholdTemperature{0.0};
    double pm_KcFactor{0.0};
    double pm_TemperatureLimitForLiquidWater{0.0};
    double pm_CorrectionSnow{0.0};
    double pm_CorrectionRain{0.0};
    double pm_SnowMaxAdditionalDensity{0.0};
    double pm_NewSnowDensityMin{0.0};
    double pm_SnowRetentionCapacityMin{0.0};
    double pm_RefreezeParameter1{0.0};
    double pm_RefreezeParameter2{0.0};
    double pm_RefreezeTemperature{0.0};
    double pm_SnowMeltTemperature{0.0};
    double pm_SnowPacking{0.0};
    double pm_SnowRetentionCapacityMax{0.0};
    double pm_EvaporationZeta{0.0};
    double pm_XSACriticalSoilMoisture{0.0};
    double pm_MaximumEvaporationImpactDepth{0.0};
    double pm_MaxPercolationRate{0.0};
    double pm_MoistureInitValue{0.0};
	};

	//----------------------------------------------------------------------------

	/**
	 * Class that holds information about user defined soil temperature parameters.
	 * @author Xenia Specka
	 */
  struct UserSoilTemperatureParameters
	{
    UserSoilTemperatureParameters(){}

    UserSoilTemperatureParameters(json11::Json object);

    json11::Json to_json() const;

    std::string toString() const { return to_json().dump(); }

    double pt_NTau{0.0};
    double pt_InitialSurfaceTemperature{0.0};
    double pt_BaseTemperature{0.0};
    double pt_QuartzRawDensity{0.0};
    double pt_DensityAir{0.0};
    double pt_DensityWater{0.0};
    double pt_DensityHumus{0.0};
    double pt_SpecificHeatCapacityAir{0.0};
    double pt_SpecificHeatCapacityQuartz{0.0};
    double pt_SpecificHeatCapacityWater{0.0};
    double pt_SpecificHeatCapacityHumus{0.0};
    double pt_SoilAlbedo{0.0};
    double pt_SoilMoisture{0.25};
	};

	//----------------------------------------------------------------------------

	/**
	 * Class that holds information about user defined soil transport parameters.
	 * @author Xenia Specka
	 */
  struct UserSoilTransportParameters
	{
    UserSoilTransportParameters(){}

    UserSoilTransportParameters(json11::Json object);

    json11::Json to_json() const;

    std::string toString() const { return to_json().dump(); }

    double pq_DispersionLength{0.0};
    double pq_AD{0.0};
    double pq_DiffusionCoefficientStandard{0.0};
    double pq_NDeposition{0.0};
	};

	//----------------------------------------------------------------------------

	/**
	 * Class that holds information about user-defined soil organic parameters.
	 * @author Claas Nendel
	 */
  struct UserSoilOrganicParameters
	{
    UserSoilOrganicParameters(){}

    UserSoilOrganicParameters(json11::Json object);

    json11::Json to_json() const;

    std::string toString() const { return to_json().dump(); }

    double po_SOM_SlowDecCoeffStandard{4.30e-5}; // 4.30e-5 [d-1], Bruun et al. 2003 4.3e-5
    double po_SOM_FastDecCoeffStandard{1.40e-4}; // 1.40e-4 [d-1], from DAISY manual 1.4e-4
    double po_SMB_SlowMaintRateStandard{1.00e-3}; // 1.00e-3 [d-1], from DAISY manual original 1.8e-3
    double po_SMB_FastMaintRateStandard{1.00e-2}; // 1.00e-2 [d-1], from DAISY manual
    double po_SMB_SlowDeathRateStandard{1.00e-3}; // 1.00e-3 [d-1], from DAISY manual
    double po_SMB_FastDeathRateStandard{1.00e-2}; // 1.00e-2 [d-1], from DAISY manual
    double po_SMB_UtilizationEfficiency{0.60}; // 0.60 [], from DAISY manual 0.6
    double po_SOM_SlowUtilizationEfficiency{0.40}; // 0.40 [], from DAISY manual 0.4
    double po_SOM_FastUtilizationEfficiency{0.50}; // 0.50 [], from DAISY manual 0.5
    double po_AOM_SlowUtilizationEfficiency{0.40}; // 0.40 [], from DAISY manual original 0.13
    double po_AOM_FastUtilizationEfficiency{0.10}; // 0.10 [], from DAISY manual original 0.69
    double po_AOM_FastMaxC_to_N{1000.0}; // 1000.0
    double po_PartSOM_Fast_to_SOM_Slow{0.30}; // 0.30 [], Bruun et al. 2003
    double po_PartSMB_Slow_to_SOM_Fast{0.60}; // 0.60 [], from DAISY manual
    double po_PartSMB_Fast_to_SOM_Fast{0.60}; // 0.60 [], from DAISY manual
    double po_PartSOM_to_SMB_Slow{0.0150}; // 0.0150 [], optimised
    double po_PartSOM_to_SMB_Fast{0.0002}; // 0.0002 [], optimised
    double po_CN_Ratio_SMB{6.70}; // 6.70 [], from DAISY manual
    double po_LimitClayEffect{0.25}; // 0.25 [kg kg-1], from DAISY manual
    double po_AmmoniaOxidationRateCoeffStandard{1.0e-1}; // 1.0e-1 [d-1], from DAISY manual
    double po_NitriteOxidationRateCoeffStandard{9.0e-1}; // 9.0e-1 [d-1], fudged by Florian Stange
    double po_TransportRateCoeff{0.1}; // 0.1 [d-1], from DAISY manual
    double po_SpecAnaerobDenitrification{0.1}; // 0.1 [g gas-N g CO2-C-1]
    double po_ImmobilisationRateCoeffNO3{0.5}; // 0.5 [d-1]
    double po_ImmobilisationRateCoeffNH4{0.5}; // 0.5 [d-1]
    double po_Denit1{0.2}; // 0.2 Denitrification parameter
    double po_Denit2{0.8}; // 0.8 Denitrification parameter
    double po_Denit3{0.9}; // 0.9 Denitrification parameter
    double po_HydrolysisKM{0.00334}; // 0.00334 from Tabatabai 1973
    double po_ActivationEnergy{41000.0}; // 41000.0 from Gould et al. 1973
    double po_HydrolysisP1{4.259e-12}; // 4.259e-12 from Sadeghi et al. 1988
    double po_HydrolysisP2{1.408e-12}; // 1.408e-12 from Sadeghi et al. 1988
    double po_AtmosphericResistance{0.0025}; // 0.0025 [s m-1], from Sadeghi et al. 1988
    double po_N2OProductionRate{0.5}; // 0.5 [d-1]
    double po_Inhibitor_NH3{1.0}; // 1.0 [kg N m-3] NH3-induced inhibitor for nitrite oxidation
	};

	//----------------------------------------------------------------------------

  struct SensitivityAnalysisParameters
	{
    SensitivityAnalysisParameters();

		// soilmoisture module parameters
    double p_MeanFieldCapacity{UNDEFINED};
    double p_MeanBulkDensity{UNDEFINED};
    double p_HeatConductivityFrozen{UNDEFINED};
    double p_HeatConductivityUnfrozen{UNDEFINED};
    double p_LatentHeatTransfer{UNDEFINED};
    double p_ReducedHydraulicConductivity{UNDEFINED};
    double vs_FieldCapacity{UNDEFINED};
    double vs_Saturation{UNDEFINED};
    double vs_PermanentWiltingPoint{UNDEFINED};
    double vs_SoilMoisture{UNDEFINED};
    double vs_SoilTemperature{UNDEFINED};

		// crop parameters
    double vc_SoilCoverage{UNDEFINED};
    double vc_MaxRootingDepth{UNDEFINED};
    double vc_RootDiameter{UNDEFINED};

		CropParameters crop_parameters;
		OrganicMatterParameters organic_matter_parameters;
    int sa_crop_id{-1};
	};

	//----------------------------------------------------------------------------

	/**
	 * @brief Central data distribution class.
	 *
	 * Class that holds pointers and direct information of user defined parameters.
	 *
	 * @author Xenia Specka
	 */
	class CentralParameterProvider
	{
	public:
    CentralParameterProvider();

		UserCropParameters userCropParameters;
		UserEnvironmentParameters userEnvironmentParameters;
		UserSoilMoistureParameters userSoilMoistureParameters;
		UserSoilTemperatureParameters userSoilTemperatureParameters;
		UserSoilTransportParameters userSoilTransportParameters;
		UserSoilOrganicParameters userSoilOrganicParameters;
		SensitivityAnalysisParameters sensitivityAnalysisParameters;
		UserInitialValues userInitValues;

//    Soil::CapillaryRiseRates capillaryRiseRates;

		double getPrecipCorrectionValue(int month) const;
		void setPrecipCorrectionValue(int month, double value);

		bool writeOutputFiles{ false };

	private:
		std::vector<double> precipCorrectionValues;
	};
}

#endif