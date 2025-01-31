/*
 * Copyright (C) 2021 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
#ifndef IGNITION_GAZEBO_COMPONENTS_SPHERICALCOORDINATES_HH_
#define IGNITION_GAZEBO_COMPONENTS_SPHERICALCOORDINATES_HH_

#include <ignition/math/SphericalCoordinates.hh>
#include <ignition/gazebo/components/Factory.hh>
#include <ignition/gazebo/components/Component.hh>
#include <ignition/gazebo/components/Serialization.hh>
#include <ignition/gazebo/Conversions.hh>
#include <ignition/gazebo/config.hh>

namespace ignition
{
namespace gazebo
{
// Inline bracket to help doxygen filtering.
inline namespace IGNITION_GAZEBO_VERSION_NAMESPACE {
namespace serializers
{
  using SphericalCoordinatesSerializer =
      serializers::ComponentToMsgSerializer<math::SphericalCoordinates,
      msgs::SphericalCoordinates>;
}

namespace components
{
  /// \brief This component holds the spherical coordinates of the world origin.
  using SphericalCoordinates =
      Component<math::SphericalCoordinates, class SphericalCoordinatesTag,
      serializers::SphericalCoordinatesSerializer>;
  IGN_GAZEBO_REGISTER_COMPONENT(
      "ign_gazebo_components.SphericalCoordinates", SphericalCoordinates)
}
}
}
}

#endif
