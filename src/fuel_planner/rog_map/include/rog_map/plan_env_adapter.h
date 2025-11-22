/**
* This file is part of ROG-Map
*
* Copyright 2024 Yunfan REN, MaRS Lab, University of Hong Kong, <mars.hku.hk>
* Developed by Yunfan REN <renyf at connect dot hku dot hk>
* Adapter for plan_env compatibility
*/

#pragma once

#include <rog_map/rog_map.h>
#include <utils/raycaster.h>
#include <memory>

namespace fast_planner {

// Forward declarations for compatibility with plan_env
class SDFMap;
class EDTEnvironment;

/**
 * @brief RayCaster adapter - provides compatibility with plan_env's RayCaster interface
 */
class RayCaster {
public:
  typedef std::shared_ptr<RayCaster> Ptr;

  RayCaster() {
    raycaster_ = std::make_shared<rog_map::raycaster::RayCaster>();
  }

  ~RayCaster() = default;

  void setParams(const double& res, const Eigen::Vector3d& origin) {
    raycaster_->setResolution(res);
    origin_ = origin;
    resolution_ = res;
  }

  bool setInput(const Eigen::Vector3d& start, const Eigen::Vector3d& end) {
    return raycaster_->setInput(start, end);
  }

  // Alias for compatibility with plan_env
  bool input(const Eigen::Vector3d& start, const Eigen::Vector3d& end) {
    return setInput(start, end);
  }

  bool step(Eigen::Vector3d& ray_pt) {
    return raycaster_->step(ray_pt);
  }

  // Alias for compatibility with plan_env - returns next position
  bool nextId(Eigen::Vector3d& ray_pt) {
    return step(ray_pt);
  }

  // Overload for index-based raycasting
  bool nextId(Eigen::Vector3i& idx) {
    Eigen::Vector3d ray_pt;
    bool result = step(ray_pt);
    if (result) {
      // Convert position to index
      // Assuming the index is calculated from position and origin
      for (int i = 0; i < 3; ++i) {
        idx(i) = static_cast<int>(std::floor((ray_pt(i) - origin_(i)) / resolution_));
      }
    }
    return result;
  }

  // Get underlying ROG raycaster
  rog_map::raycaster::RayCaster::Ptr getROGRayCaster() const {
    return raycaster_;
  }

private:
  rog_map::raycaster::RayCaster::Ptr raycaster_;
  Eigen::Vector3d origin_;
  double resolution_ = 0.1;
};

/**
 * @brief Adapter class to make ROGMap compatible with plan_env's SDFMap interface
 */
class SDFMap {
public:
  enum OCCUPANCY { UNKNOWN = 1, FREE = 0, OCCUPIED = 2 };

  typedef std::shared_ptr<SDFMap> Ptr;

  SDFMap() = default;
  ~SDFMap() = default;

  void setROGMap(rog_map::ROGMap::Ptr rog_map) {
    rog_map_ = rog_map;
  }

  /**
   * @brief Initialize map with ROS node handle
   */
  void initMap(ros::NodeHandle& nh) {
    rog_map_ = std::make_shared<rog_map::ROGMap>(nh);
  }

  /**
   * @brief Get occupancy state at position
   * @return UNKNOWN (1), FREE (0), or OCCUPIED (2)
   */
  int getOccupancy(const Eigen::Vector3d& pos) const {
    if (!rog_map_) return UNKNOWN;
    
    rog_map::Vec3f pos_f = pos.cast<rog_map::decimal_t>();
    
    if (rog_map_->isOccupied(pos_f)) {
      return OCCUPIED;
    } else if (rog_map_->isKnownFree(pos_f)) {
      return FREE;
    } else {
      return UNKNOWN;
    }
  }

  int getOccupancy(const Eigen::Vector3i& id) const {
    Eigen::Vector3d pos;
    indexToPos(id, pos);
    return getOccupancy(pos);
  }

  /**
   * @brief Get inflated occupancy at position
   * @return 1 if occupied/inflated, 0 otherwise
   */
  int getInflateOccupancy(const Eigen::Vector3d& pos) const {
    if (!rog_map_) return 0;
    
    rog_map::Vec3f pos_f = pos.cast<rog_map::decimal_t>();
    
    if (rog_map_->isOccupiedInflate(pos_f)) {
      return 1;
    }
    return 0;
  }

  int getInflateOccupancy(const Eigen::Vector3i& id) const {
    Eigen::Vector3d pos;
    indexToPos(id, pos);
    return getInflateOccupancy(pos);
  }

  /**
   * @brief Get distance from ESDF
   */
  double getDistance(const Eigen::Vector3d& pos) const {
    if (!rog_map_) {
      return 0.0;
    }
    
    auto esdf_map = rog_map_->getESDFMap();
    if (!esdf_map) {
      return 0.0;
    }
    
    rog_map::Vec3f pos_f = pos.cast<rog_map::decimal_t>();
    return esdf_map->getDistance(pos_f);
  }

  double getDistance(const Eigen::Vector3i& id) const {
    if (!rog_map_) {
      return 0.0;
    }
    
    auto esdf_map = rog_map_->getESDFMap();
    if (!esdf_map) {
      return 0.0;
    }
    
    return esdf_map->getDistance(id);
  }

  /**
   * @brief Get distance with gradient
   */
  double getDistWithGrad(const Eigen::Vector3d& pos, Eigen::Vector3d& grad) const {
    if (!rog_map_) {
      grad.setZero();
      return 0.0;
    }
    
    auto esdf_map = rog_map_->getESDFMap();
    if (!esdf_map) {
      grad.setZero();
      return 0.0;
    }
    
    rog_map::Vec3f pos_f = pos.cast<rog_map::decimal_t>();
    double dist;
    esdf_map->evaluateEDT(pos, dist);
    esdf_map->evaluateFirstGrad(pos, grad);
    return dist;
  }

  /**
   * @brief Check if position is inside map bounds
   */
  bool isInMap(const Eigen::Vector3d& pos) const {
    if (!rog_map_) return false;
    rog_map::Vec3f pos_f = pos.cast<rog_map::decimal_t>();
    return rog_map_->insideLocalMap(pos_f);
  }

  bool isInMap(const Eigen::Vector3i& idx) const {
    if (!rog_map_) return false;
    rog_map::Vec3i idx_i = idx.cast<int>();
    return rog_map_->insideLocalMap(idx_i);
  }

  /**
   * @brief Check if position is inside valid box
   */
  bool isInBox(const Eigen::Vector3d& pos) const {
    return isInMap(pos);
  }

  bool isInBox(const Eigen::Vector3i& id) const {
    return isInMap(id);
  }

  /**
   * @brief Get map region (origin and size)
   */
  void getRegion(Eigen::Vector3d& ori, Eigen::Vector3d& size) const {
    if (!rog_map_) {
      ori.setZero();
      size.setZero();
      return;
    }
    
    rog_map::Vec3f origin_f = rog_map_->getLocalMapOrigin();
    rog_map::Vec3f size_f = rog_map_->getLocalMapSize();
    
    ori = origin_f.cast<double>();
    size = size_f.cast<double>();
  }

  /**
   * @brief Get bounding box
   */
  void getBox(Eigen::Vector3d& bmin, Eigen::Vector3d& bmax) const {
    if (!rog_map_) {
      bmin.setZero();
      bmax.setZero();
      return;
    }
    
    rog_map::Vec3f origin = rog_map_->getLocalMapOrigin();
    rog_map::Vec3f size = rog_map_->getLocalMapSize();
    
    bmin = origin.cast<double>();
    bmax = (origin + size).cast<double>();
  }

  /**
   * @brief Bound a box to map limits (alias for getBox)
   */
  void boundBox(Eigen::Vector3d& bmin, Eigen::Vector3d& bmax) const {
    getBox(bmin, bmax);
  }

  /**
   * @brief Get map resolution
   */
  double getResolution() const {
    if (!rog_map_) return 0.1;
    return rog_map_->getResolution();
  }

  /**
   * @brief Update ESDF
   */
  void updateESDF3d() {
    if (!rog_map_) return;
    
    auto esdf_map = rog_map_->getESDFMap();
    if (esdf_map) {
      rog_map::Vec3f cur_pos = rog_map_->getRobotState().p;
      esdf_map->updateESDF3D(cur_pos);
    }
  }

  /**
   * @brief Position to index conversion
   */
  void posToIndex(const Eigen::Vector3d& pos, Eigen::Vector3i& id) const {
    if (!rog_map_) {
      id.setZero();
      return;
    }
    
    // Calculate index manually since posToGlobalIndex is protected
    double resolution = rog_map_->getResolution();
    rog_map::Vec3f origin = rog_map_->getLocalMapOrigin();
    rog_map::Vec3f pos_f = pos.cast<rog_map::decimal_t>();
    
    for (int i = 0; i < 3; ++i) {
      id(i) = floor((pos_f(i) - origin(i)) / resolution);
    }
  }

  /**
   * @brief Index to position conversion
   */
  void indexToPos(const Eigen::Vector3i& id, Eigen::Vector3d& pos) const {
    if (!rog_map_) {
      pos.setZero();
      return;
    }
    
    // Calculate position manually since globalIndexToPos is protected
    double resolution = rog_map_->getResolution();
    rog_map::Vec3f origin = rog_map_->getLocalMapOrigin();
    
    for (int i = 0; i < 3; ++i) {
      pos(i) = (id(i) + 0.5) * resolution + origin(i);
    }
  }

  /**
   * @brief Get total number of voxels
   */
  int getVoxelNum() const {
    if (!rog_map_) return 0;
    
    // Calculate voxel number from map size and resolution
    rog_map::Vec3f size = rog_map_->getLocalMapSize();
    double resolution = rog_map_->getResolution();
    
    int voxel_x = static_cast<int>(size(0) / resolution);
    int voxel_y = static_cast<int>(size(1) / resolution);
    int voxel_z = static_cast<int>(size(2) / resolution);
    
    return voxel_x * voxel_y * voxel_z;
  }

  /**
   * @brief Get updated box region
   */
  void getUpdatedBox(Eigen::Vector3d& bmin, Eigen::Vector3d& bmax, bool reset = false) const {
    // For now, return the entire map box as the updated region
    getBox(bmin, bmax);
  }

  /**
   * @brief Convert index to linear address
   */
  int toAddress(const Eigen::Vector3i& id) const {
    if (!rog_map_) return -1;
    
    // Calculate voxel dimensions
    rog_map::Vec3f size = rog_map_->getLocalMapSize();
    double resolution = rog_map_->getResolution();
    
    int voxel_x = static_cast<int>(size(0) / resolution);
    int voxel_y = static_cast<int>(size(1) / resolution);
    int voxel_z = static_cast<int>(size(2) / resolution);
    
    // Bounds check
    if (id(0) < 0 || id(0) >= voxel_x ||
        id(1) < 0 || id(1) >= voxel_y ||
        id(2) < 0 || id(2) >= voxel_z) {
      return -1;
    }
    
    // Convert to linear address (row-major order)
    return id(0) + id(1) * voxel_x + id(2) * voxel_x * voxel_y;
  }

  int toAddress(int x, int y, int z) const {
    Eigen::Vector3i id(x, y, z);
    return toAddress(id);
  }

  /**
   * @brief Get the underlying ROGMap pointer
   */
  rog_map::ROGMap::Ptr getROGMap() const {
    return rog_map_;
  }

private:
  rog_map::ROGMap::Ptr rog_map_;
};

/**
 * @brief Adapter class to make ROGMap compatible with plan_env's EDTEnvironment interface
 */
class EDTEnvironment {
public:
  typedef std::shared_ptr<EDTEnvironment> Ptr;

  EDTEnvironment() = default;
  ~EDTEnvironment() = default;

  /**
   * @brief Initialize with SDFMap adapter
   */
  void init() {
    // Initialization handled by sdf_map_
  }

  /**
   * @brief Set the SDF map
   */
  void setMap(std::shared_ptr<SDFMap>& map) {
    sdf_map_ = map;
  }

  /**
   * @brief Evaluate EDT with gradient
   */
  void evaluateEDTWithGrad(const Eigen::Vector3d& pos, double time, 
                          double& dist, Eigen::Vector3d& grad) {
    if (!sdf_map_) {
      dist = 0.0;
      grad.setZero();
      return;
    }
    
    dist = sdf_map_->getDistWithGrad(pos, grad);
  }

  /**
   * @brief Evaluate coarse EDT
   */
  double evaluateCoarseEDT(Eigen::Vector3d& pos, double time) {
    if (!sdf_map_) return 0.0;
    return sdf_map_->getDistance(pos);
  }

  // Public member for compatibility with existing code
  std::shared_ptr<SDFMap> sdf_map_;
};

}  // namespace fast_planner

