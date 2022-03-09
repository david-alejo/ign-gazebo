/*
 * Copyright (C) 2020 Open Source Robotics Foundation
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
#ifndef IGNITION_GAZEBO_GUI_GUIEVENTS_HH_
#define IGNITION_GAZEBO_GUI_GUIEVENTS_HH_

#include <QEvent>
#include <QMap>
#include <QString>

#include <set>
#include <string>
#include <utility>
#include <vector>

#include <ignition/math/Vector3.hh>
#include <ignition/utils/ImplPtr.hh>
#include <sdf/Element.hh>

#include "ignition/gazebo/gui/Export.hh"
#include "ignition/gazebo/Entity.hh"
#include "ignition/gazebo/config.hh"

namespace ignition
{
namespace gazebo
{
namespace gui {
// Inline bracket to help doxygen filtering.
inline namespace IGNITION_GAZEBO_VERSION_NAMESPACE {
/// \brief Namespace for all events. Refer to the EventManager class for
/// more information about events.
namespace events
{
  /// \brief Event that notifies when new entities have been selected.
  class IGNITION_GAZEBO_GUI_VISIBLE EntitiesSelected : public QEvent
  {
    /// \brief Constructor
    /// \param[in] _entities All the selected entities
    /// \param[in] _fromUser True if the event was directly generated by the
    /// user, false in case it's been propagated through a different mechanism.
    public: explicit EntitiesSelected(
        const std::vector<Entity> &_entities,  // NOLINT
        bool _fromUser = false)
        : QEvent(kType), entities(_entities), fromUser(_fromUser)
    {
    }

    /// \brief Get the data sent with the event.
    /// \return The entities being selected.
    public: std::vector<Entity> Data() const
    {
      return this->entities;
    }

    /// \brief Get whether the event was generated by the user.
    /// \return True for the user.
    public: bool FromUser() const
    {
      return this->fromUser;
    }

    /// \brief Unique type for this event.
    static const QEvent::Type kType = QEvent::Type(QEvent::User + 1);

    /// \brief The selected entities.
    private: std::vector<Entity> entities;

    /// \brief Whether the event was generated by the user,
    private: bool fromUser{false};
  };

  /// \brief Event that notifies when all entities have been deselected.
  class IGNITION_GAZEBO_GUI_VISIBLE DeselectAllEntities : public QEvent
  {
    /// \brief Constructor
    /// \param[in] _fromUser True if the event was directly generated by the
    /// user, false in case it's been propagated through a different mechanism.
    public: explicit DeselectAllEntities(bool _fromUser = false)
        : QEvent(kType), fromUser(_fromUser)
    {
    }

    /// \brief Get whether the event was generated by the user.
    /// \return True for the user.
    public: bool FromUser() const
    {
      return this->fromUser;
    }

    /// \brief Unique type for this event.
    static const QEvent::Type kType = QEvent::Type(QEvent::User + 2);

    /// \brief Whether the event was generated by the user,
    private: bool fromUser{false};
  };

  /// \brief Event that contains entities newly created or removed from the
  /// GUI, but that aren't present on the server yet.
  /// \sa NewRemovedEntities
  class IGNITION_GAZEBO_GUI_VISIBLE GuiNewRemovedEntities : public QEvent
  {
    /// \brief Constructor
    /// \param[in] _newEntities Set of newly created entities
    /// \param[in] _removedEntities Set of recently removed entities
    public: GuiNewRemovedEntities(const std::set<Entity> &_newEntities,
                const std::set<Entity> &_removedEntities);

    /// \brief Get the set of newly created entities
    public: const std::set<Entity> &NewEntities() const;

    /// \brief Get the set of recently removed entities
    public: const std::set<Entity> &RemovedEntities() const;

    /// \brief Unique type for this event.
    static const QEvent::Type kType = QEvent::Type(QEvent::User + 3);

    /// \internal
    /// \brief Private data pointer
    IGN_UTILS_IMPL_PTR(dataPtr)
  };

  /// \brief Event that notifies when new entities have been created or removed
  /// on the server. This is a duplication of what `GuiSystem`s would get from
  /// `EachNew` / `EachRemoved` ECM calls.
  /// \sa GuiNewRemovedEntities
  class IGNITION_GAZEBO_GUI_VISIBLE NewRemovedEntities : public QEvent
  {
    /// \brief Constructor
    /// \param[in] _newEntities Set of newly created entities
    /// \param[in] _removedEntities Set of recently removed entities
    public: NewRemovedEntities(const std::set<Entity> &_newEntities,
                const std::set<Entity> &_removedEntities);

    /// \brief Get the set of newly created entities
    public: const std::set<Entity> &NewEntities() const;

    /// \brief Get the set of recently removed entities
    public: const std::set<Entity> &RemovedEntities() const;

    /// \brief Unique type for this event.
    static const QEvent::Type kType = QEvent::Type(QEvent::User + 4);

    /// \internal
    /// \brief Private data pointer
    IGN_UTILS_IMPL_PTR(dataPtr)
  };

  /// \brief True if a transform control is currently active (translate /
  /// rotate / scale). False if we're in selection mode.
  class IGNITION_GAZEBO_GUI_VISIBLE TransformControlModeActive : public QEvent
  {
    /// \brief Constructor
    /// \param[in] _tranformModeActive is the transform control mode active
    public: explicit TransformControlModeActive(const bool _tranformModeActive)
        : QEvent(kType), tranformModeActive(_tranformModeActive)
    {
    }

    /// \brief Unique type for this event.
    static const QEvent::Type kType = QEvent::Type(QEvent::User + 6);

    /// \brief Get the event's value.
    public: bool TransformControlActive()
    {
      return this->tranformModeActive;
    }

    /// \brief True if a transform mode is active.
    private: bool tranformModeActive;
  };

  /// \brief Event that notifies an entity is to be added to the model editor
  class IGNITION_GAZEBO_GUI_VISIBLE ModelEditorAddEntity : public QEvent
  {
    /// \brief Constructor
    /// \param[in] _entity Entity added
    /// \param[in] _type Entity type
    /// \param[in] _parent Parent entity.
    public: explicit ModelEditorAddEntity(QString _entity, QString _type,
                ignition::gazebo::Entity _parent);

    /// \brief Get the entity to add
    public: QString Entity() const;

    /// \brief Get the entity type
    public: QString EntityType() const;


    /// \brief Get the parent entity to add the entity to
    public: ignition::gazebo::Entity ParentEntity() const;

    /// \brief Get the data map.
    /// \return the QMap of string, string holding custom data.
    public: QMap<QString, QString> &Data();

    static const QEvent::Type kType = QEvent::Type(QEvent::User + 7);

    /// \internal
    /// \brief Private data pointer
    IGN_UTILS_IMPL_PTR(dataPtr)
  };

  /// \brief Event that notifies a visual plugin is to be loaded
  class IGNITION_GAZEBO_GUI_VISIBLE VisualPlugin: public QEvent
  {
    /// \brief Constructor
    /// \param[in] _entity Visual entity id
    /// \param[in] _elem Visual plugin SDF element
    public: explicit VisualPlugin(ignition::gazebo::Entity _entity,
                const sdf::ElementPtr &_elem);

    /// \brief Get the entity to load the visual plugin for
    public: ignition::gazebo::Entity Entity() const;

    /// \brief Get the sdf element of the visual plugin
    public: sdf::ElementPtr Element() const;

    static const QEvent::Type kType = QEvent::Type(QEvent::User + 8);

    /// \internal
    /// \brief Private data pointer
    IGN_UTILS_IMPL_PTR(dataPtr)
  };
}  // namespace events
}
}  // namespace gui
}  // namespace gazebo
}  // namespace ignition

#endif  // IGNITION_GAZEBO_GUI_GUIEVENTS_HH_
