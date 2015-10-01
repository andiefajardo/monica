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

#ifndef SOILCOLUMN_H_
#define SOILCOLUMN_H_

/**
 * @file soilcolumn.h
 *
 * @brief This file contains the declaration of classes AOM_Properties,  SoilLayer, SoilColumn
 * and FertilizerTriggerThunk.
 *
 * @see Monica::AOM_Properties
 * @see Monica::SoilLayer
 * @see Monica::SoilColumn
 * @see Monica::FertilizerTriggerThunk
 */

#include <vector>
#include <list>
#include <iostream>

#include "monica-parameters.h"

namespace Monica
{
  // forward declarations
  class SoilLayer;
  class SoilColumn;
  class CropGrowth;

  //std::vector<AOM_Properties> vo_AOM_Pool;

  /**
   * @author Claas Nendel, Michael Berg
   *
   * @brief Storage class for the transformation of organic substance.
   *
   * Class stores data and parameters used in the AOM (Added Organic Matter) circle,
   * that is displayed in the picture below. The AOM-Circle is a description for the
   * transformation of organic substance.
   *
   * <img src="../images/aom-diagramm.png" width="600" height="420">
   */
  struct AOM_Properties
  {
    double vo_AOM_Slow{0.0}; //!< C content in slowly decomposing added organic matter pool [kgC m-3]
    double vo_AOM_Fast{0.0}; //!< C content in rapidly decomposing added organic matter pool [kgC m-3]

    double vo_AOM_SlowDecRate_to_SMB_Slow{0.0}; //!< Rate for slow AOM consumed by SMB Slow is calculated.
    double vo_AOM_SlowDecRate_to_SMB_Fast{0.0}; //!< Rate for slow AOM consumed by SMB Fast is calculated.
    double vo_AOM_FastDecRate_to_SMB_Slow{0.0}; //!< Rate for fast AOM consumed by SMB Slow is calculated.
    double vo_AOM_FastDecRate_to_SMB_Fast{0.0}; //!< Rate for fast AOM consumed by SMB Fast is calculated.

    double vo_AOM_SlowDecCoeff{0.0}; //!< Is dependent on environment
    double vo_AOM_FastDecCoeff{0.0}; //!< Is dependent on environment

    double vo_AOM_SlowDecCoeffStandard{1.0}; //!< Decomposition rate coefficient for slow AOM pool at standard conditions
    double vo_AOM_FastDecCoeffStandard{1.0}; //!< Decomposition rate coefficient for fast AOM pool at standard conditions

    double vo_PartAOM_Slow_to_SMB_Slow{0.0}; //!< Partial transformation from AOM to SMB (soil microbiological biomass) for slow AOMs.
    double vo_PartAOM_Slow_to_SMB_Fast{0.0}; //!< Partial transformation from AOM to SMB (soil microbiological biomass) for fast AOMs.

    double vo_CN_Ratio_AOM_Slow{1.0}; //!< Used for calculation N-value if only C-value is known. Usually a constant value.
    double vo_CN_Ratio_AOM_Fast{1.0}; //!< C-N-Ratio is dependent on the nutritional condition of the plant.

    int vo_DaysAfterApplication{0}; //!< Fertilization parameter
    double vo_AOM_DryMatterContent{0.0}; //!< Fertilization parameter
    double vo_AOM_NH4Content{0.0}; //!< Fertilization parameter

    double vo_AOM_SlowDelta{0.0}; //!< Difference of AOM slow between to timesteps
    double vo_AOM_FastDelta{0.0}; //!< Difference of AOM fast between to timesteps

    bool incorporation{false};  //!< True if organic fertilizer is added with a subsequent incorporation.
  };

  //----------------------------------------------------------------------------

  /**
   * @author Claas Nendel, Michael Berg
   *
   * @brief class that stores information and properties about a soil layer.
   *
   * Storage class for soil layer properties e.g. saturation, field capacity, etc.
   * Right now all layers are expected to be from the same size, but this code
   * allows different sizes for a layer, too.
   *
   */
  class SoilLayer
  {
  public:
    SoilLayer();

    SoilLayer(const UserInitialValues* initParams,
              const SensitivityAnalysisParameters* saParams);

    SoilLayer(double vs_LayerThickness,
              const Soil::SoilParameters& soilParams,
              const UserInitialValues* initParams,
              const SensitivityAnalysisParameters* saParams);

    void calc_vs_SoilMoisture_pF();

    // calculations with Van Genuchten parameters
    double get_Saturation();

    double get_FieldCapacity();

    double get_PermanentWiltingPoint();

    //! Sets value of soil organic matter parameter.
    void set_SoilOrganicMatter(double som) { _vs_SoilOrganicMatter = som; }

    //! Sets value for soil organic carbon.
    void set_SoilOrganicCarbon(double soc) { _vs_SoilOrganicCarbon = soc; }

    //! Returns bulk density of soil layer [kg m-3]
    double vs_SoilBulkDensity() const { return _vs_SoilBulkDensity; }

    //! Returns pH value of soil layer
    double get_SoilpH() const { return vs_SoilpH; }

    //! Returns soil water pressure head as common logarithm pF.
    double vs_SoilMoisture_pF()
    {
      calc_vs_SoilMoisture_pF();
      return _vs_SoilMoisture_pF;
    }

    //! soil ammonium content [kg N m-3]
    double get_SoilNH4() const { return vs_SoilNH4; }

    //! soil nitrite content [kg N m-3]
    double get_SoilNO2() const { return vs_SoilNO2; }

    //! soil nitrate content [kg N m-3]
    double get_SoilNO3() const { return vs_SoilNO3; }

    //! soil carbamide content [kg m-3]
    double get_SoilCarbamid() const { return vs_SoilCarbamid; }

    //! soil mineral N content [kg m-3]
    double get_SoilNmin() const { return vs_SoilNO3 + vs_SoilNO2 + vs_SoilNH4; }

    double get_Vs_SoilMoisture_m3() const;

    void set_Vs_SoilMoisture_m3(double ms);

    double get_Vs_SoilTemperature() const;

    void set_Vs_SoilTemperature(double st);

    // members ------------------------------------------------------------

    double vs_LayerThickness; //!< Soil layer's vertical extension [m]
    double vs_SoilSandContent{0.9}; //!< Soil layer's sand content [kg kg-1]
    double vs_SoilClayContent{0.05}; //!< Soil layer's clay content [kg kg-1] (Ton)
    double vs_SoilStoneContent{0.0}; //!< Soil layer's stone content in soil [kg kg-1]
    double vs_SoilSiltContent() const; //!< Soil layer's silt content [kg kg-1] (Schluff)
    std::string vs_SoilTexture;

    double vs_SoilpH{7.0}; //!< Soil pH value []
    double vs_SoilOrganicCarbon() const; //!< Soil layer's organic carbon content [kg C kg-1]
    double vs_SoilOrganicMatter() const; //!< Soil layer's organic matter content [kg OM kg-1]

    double vs_SoilMoistureOld_m3{0.25}; //!< Soil layer's moisture content of previous day [m3 m-3]
    double vs_SoilWaterFlux{0.0}; //!< Water flux at the upper boundary of the soil layer [l m-2]
    double vs_Lambda{0.5}; //!< Soil water conductivity coefficient []
    double vs_FieldCapacity{0.21};
    double vs_Saturation{0.43};
    double vs_PermanentWiltingPoint{0.08};

    std::vector<AOM_Properties> vo_AOM_Pool; //!< List of different added organic matter pools in soil layer

    double vs_SOM_Slow{0.0}; //!< C content of soil organic matter slow pool [kg C m-3]
    double vs_SOM_Fast{0.0}; //!< C content of soil organic matter fast pool size [kg C m-3]
    double vs_SMB_Slow{0.0}; //!< C content of soil microbial biomass slow pool size [kg C m-3]
    double vs_SMB_Fast{0.0}; //!< C content of soil microbial biomass fast pool size [kg C m-3]

    // anorganische Stickstoff-Formen
    double vs_SoilCarbamid{0.0}; //!< Soil layer's carbamide-N content [kg Carbamide-N m-3]
    double vs_SoilNH4{0.0001}; //!< Soil layer's NH4-N content [kg NH4-N m-3]
    double vs_SoilNO2{0.001}; //!< Soil layer's NO2-N content [kg NO2-N m-3]
    double vs_SoilNO3{0.0001}; //!< Soil layer's NO3-N content [kg NO3-N m-3]
    bool vs_SoilFrozen{false};

    const UserInitialValues* initPs{nullptr};
    const SensitivityAnalysisParameters* saPs{nullptr};

  private:
    //! only one of the two is being initialized and used for calculations
    double _vs_SoilOrganicCarbon{-1.0}; //!< Soil organic carbon content [kg C kg-1]
    double _vs_SoilOrganicMatter{-1.0}; //!< Soil organic matter content [kg OM kg-1]

    double _vs_SoilBulkDensity{0.0}; //!< Bulk density of soil [kg m-3]
    double _vs_SoilMoisture_pF{-1.0}; //!< Soil water pressure head as common logarithm [pF]

    double vs_SoilMoisture_m3{0.25}; //!< Soil layer's moisture content [m3 m-3]
    double vs_SoilTemperature{0.0}; //!< Soil layer's temperature [°C]
  };

  //----------------------------------------------------------------------------

  /**
   * @author Claas Nendel, Michael Berg
   *
   * @brief Description of a soil column that consists of a list of soil layers.

   * All layers are stored in a list and can be access by different kind of operators.
   * This code is based on a Fortran-Program so some operators are overloaded
   * to make the access of an array similar to the Fortran's way.
   *
   * @see Monica::SoilLayer
   *
   */
  class SoilColumn
  {
  public:
    SoilColumn(const GeneralParameters& generalParams,
               const Soil::SoilPMs& soilParams,
               double pm_CriticalMoistureDepth,
               const UserInitialValues& initParams,
               const SensitivityAnalysisParameters& saParams);

    void applyMineralFertiliser(MineralFertiliserParameters fertiliserPartition,
                                double amount);

    //! apply left over fertiliser after delay time
    double applyPossibleTopDressing();

    //! apply delayed fertiliser application again (yielding possible top dressing)
    double applyPossibleDelayedFerilizer();

    double applyMineralFertiliserViaNMinMethod(MineralFertiliserParameters fertiliserPartition,
                                               double vf_SamplingDepth,
                                               double vf_CropNTargetValue,
                                               double vf_CropNTargetValue30,
                                               double vf_FertiliserMaxApplication,
                                               double vf_FertiliserMinApplication,
                                               int vf_TopDressingDelay);

    bool applyIrrigationViaTrigger(double vi_IrrigationThreshold,
                                   double vi_IrrigationAmount,
                                   double vi_IrrigationNConcentration);

    void applyIrrigation(double vi_IrrigationAmount,
                         double vi_IrrigationNConcentration);
    void deleteAOMPool();


    /**
     * Returns number of layers.
     * @return Number of layers.
     */
    inline std::size_t vs_NumberOfLayers() const { return vs_SoilLayers.size(); }
		void applyTillage(double depth);

    /**
     * Returns number of organic layers. Usually the number
     * of layers in the first 30 cm depth of soil.
     * @return Number of organic layers
     */
    inline std::size_t vs_NumberOfOrganicLayers() const { return _vs_NumberOfOrganicLayers; }

    /**
     * Overloaded operator for a fortran-similar access to a C-array.
     * @return SoilLayer at given Index.
     */
    SoilLayer& operator[](size_t i_Layer) {
      return vs_SoilLayers[i_Layer];
    }

    /**
     * Overloaded operator for a fortran-similar access to a C-array.
     * @return SoilLayer at given Index.
     */
    const SoilLayer & operator[](size_t i_Layer) const {
      return vs_SoilLayers.at(i_Layer);
    }

    //! Returns a soil layer at given Index.
    SoilLayer& soilLayer(size_t i_Layer) { return vs_SoilLayers[i_Layer]; }

    //! Returns a soil layer at given Index.
    const SoilLayer& soilLayer(size_t i_Layer) const { return vs_SoilLayers.at(i_Layer); }

    //! Returns the thickness of a layer.
    //! Right now by definition all layers have the same size,
    //! therefor only the thickness of first layer is returned.
    double vs_LayerThickness() const { return vs_SoilLayers[0].vs_LayerThickness; }

    //! Returns daily crop N uptake [kg N ha-1 d-1]
    double get_DailyCropNUptake() const { return vq_CropNUptake * 10000.0; }

    std::size_t getLayerNumberForDepth(double depth);

    void put_Crop(CropGrowth* crop);

    void remove_Crop();

    double sumSoilTemperature(int layers) const;

    std::vector<SoilLayer> vs_SoilLayers; //!< Vector of all layers in column.

    double vs_SurfaceWaterStorage{0.0}; //!< Content of above-ground water storage [mm]
    double vs_InterceptionStorage{0.0}; //!< Amount of intercepted water on crop surface [mm]
    int vm_GroundwaterTable{0}; //!< Layer of current groundwater table
    double vs_FluxAtLowerBoundary{0.0}; //!< Water flux out of bottom layer
    double vq_CropNUptake{0.0}; //!< Daily amount of N taken up by the crop [kg m-2]
    double vt_SoilSurfaceTemperature{0.0};
    double vm_SnowDepth{0.0};

  private:
    std::size_t calculateNumberOfOrganicLayers();

    const GeneralParameters& generalParams;
    const Soil::SoilPMs& soilParams; //!< Vector of soil parameter

    std::size_t _vs_NumberOfOrganicLayers{0}; //!< Number of organic layers.
    double _vf_TopDressing{0.0};
    MineralFertiliserParameters _vf_TopDressingPartition;
    int _vf_TopDressingDelay{0};

    CropGrowth* cropGrowth{nullptr};

    std::list<std::function<double()>> _delayedNMinApplications;

    double pm_CriticalMoistureDepth;
  };
}

#endif