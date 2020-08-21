/*
 * Copyright (c) 2020 Valve Corporation
 * Copyright (c) 2020 LunarG, Inc.
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
 * - Richard S. Wright Jr. <richard@lunarg.com>
 * - Christophe Riccio <christophe@lunarg.com>
 */

#include "enumsettingwidget.h"

EnumSettingWidget::EnumSettingWidget(QTreeWidgetItem* item, LayerSetting* layers_settings) {
    _layer_setting = layers_settings;
    item->setText(0, layers_settings->label);
    item->setToolTip(0, layers_settings->description);

    int nCurrSel = 0;
    for (int i = 0; i < layers_settings->exclusive_labels.size(); i++) {
        this->addItem(layers_settings->exclusive_labels[i]);
        if (layers_settings->exclusive_values[i] == layers_settings->value) nCurrSel = i;
    }

    setCurrentIndex(nCurrSel);

    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(indexChanged(int)));
}

void EnumSettingWidget::indexChanged(int index) {
    _layer_setting->value = _layer_setting->exclusive_values[index];
    emit itemChanged();
}
