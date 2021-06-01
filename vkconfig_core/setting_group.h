/*
 * Copyright (c) 2020-2021 Valve Corporation
 * Copyright (c) 2020-2021 LunarG, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Authors:
 * - Christophe Riccio <christophe@lunarg.com>
 */

#pragma once

#include "setting.h"

struct SettingMetaGroup : public SettingMeta {
    static const SettingType TYPE = SETTING_GROUP;

    SettingData* Instantiate() override;
    bool Load(const QJsonObject& json_setting) override;
    std::string Export(ExportMode export_mode) const override;

   private:
    SettingMetaGroup(Layer& layer, const std::string& key);

    friend class Layer;
};

struct SettingDataGroup : public SettingData {
    SettingDataGroup(const SettingMetaGroup* meta);

    void Reset() override;
    bool Load(const QJsonObject& json_setting) override;
    bool Save(QJsonObject& json_setting) const override;
    std::string Export(ExportMode export_mode) const override;

   protected:
    virtual SettingData& Assign(const SettingData& other);

    const SettingMetaGroup* meta;
};
