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

#include "mutemessagewidget.h"

MuteMessageWidget::MuteMessageWidget(LayerSettings *layer_settings) : QWidget(nullptr) {
    layer_settings_ = layer_settings;
    list_widget_ = new QListWidget(this);
    list_widget_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    list_widget_->show();
    remove_button_ = new QPushButton(this);
    remove_button_->setText("Remove");
    remove_button_->show();

    // Load with existing settings
    if (!layer_settings_->settings_value.isEmpty()) {
        QStringList list = layer_settings_->settings_value.split(",");
        list_widget_->addItems(list);
        list_widget_->setCurrentRow(list_widget_->count() - 1);
    } else
        remove_button_->setEnabled(false);

    connect(remove_button_, SIGNAL(pressed()), this, SLOT(removePushed()));
}

void MuteMessageWidget::resizeEvent(QResizeEvent *event) {
    int nButtonHeight = 26;
    QSize parentSize = event->size();
    list_widget_->setGeometry(0, 0, parentSize.width(), parentSize.height() - nButtonHeight);
    remove_button_->setGeometry(0, parentSize.height() - nButtonHeight, parentSize.width(), nButtonHeight);
}

void MuteMessageWidget::addItem(const QString &item) {
    list_widget_->addItem(item);
    list_widget_->setCurrentRow(list_widget_->count() - 1);

    // Update Setting
    AddString(layer_settings_->settings_value, item);
    remove_button_->setEnabled(true);
    emit itemChanged();
}

void MuteMessageWidget::removePushed() {
    int nRow = list_widget_->currentRow();
    if (nRow < 0) return;

    QString itemName = list_widget_->currentItem()->text();
    list_widget_->takeItem(nRow);

    // Update Setting
    RemoveString(layer_settings_->settings_value, itemName);
    emit itemChanged();
}