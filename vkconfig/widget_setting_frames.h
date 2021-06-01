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

#include "../vkconfig_core/setting_frames.h"

#include "widget_setting.h"

#include <QString>
#include <QTreeWidgetItem>
#include <QLineEdit>
#include <QResizeEvent>
#include <QTimer>

class WidgetSettingFrames : public WidgetSettingBase {
    Q_OBJECT

   public:
    WidgetSettingFrames(QTreeWidget* tree, QTreeWidgetItem* item, const SettingMetaFrames& meta, SettingDataSet& data_set);
    virtual ~WidgetSettingFrames();

    void Refresh(RefreshAreas refresh_areas) override;

   public Q_SLOTS:
    void OnTextEdited(const QString& value);
    void OnErrorValue();
    void OnValidValue();

   Q_SIGNALS:
    void itemChanged();

   protected:
    void resizeEvent(QResizeEvent* event) override;

   private:
    void Resize();
    SettingInputError ProcessInputValue();

    const SettingDataSet& data_set;
    SettingDataFrames& data;
    const SettingMetaFrames& meta;

    std::string value_buffer;
    QLineEdit* field;
    QTimer* timer_error;
    QTimer* timer_valid;
    QSize resize;
    QPalette default_palette;
};
