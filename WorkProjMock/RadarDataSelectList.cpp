/**
  *@file RadarDataSelectList.cpp
  * QWidget providing list of radar burst data view modes
  * for selection for plot display
*/

#include "RadarDataSelectList.h"

static std::vector<std::pair<RadarDataSelectList::VIEWMODE, QString>> modes = {
    {RadarDataSelectList::VIEWMODE::REAL,  "REAL"},
    {RadarDataSelectList::VIEWMODE::IMAG,  "IMAGINARY"},
    {RadarDataSelectList::VIEWMODE::AMP,   "AMPLITUDE"},
    {RadarDataSelectList::VIEWMODE::PHASE, "PHASE"}
};

RadarDataSelectList::RadarDataSelectList(QString _name, VIEWMODE initial_mode, QWidget *parent) :
    QMultiComboBox(parent),
    name(_name),
    mode(initial_mode)

{

    for (auto mode : modes) {
        listItems[mode.first] = this->addItem(mode.second);
        activeModes[mode.first] = false;
        modeMap[mode.second] = mode.first;
    }

    connect(&this->vlist_, &QListWidget::itemChanged, this, &RadarDataSelectList::updateMode);

    this->setObjectName(name);
    this->setStyleSheet("text-color:black");
    this->SetDisplayText(name);


}

RadarDataSelectList::~RadarDataSelectList(){
}

void RadarDataSelectList::updateMode(QListWidgetItem *item){
    auto mode = modeMap.at(item->text());
    activeModes[mode] = !activeModes.at(mode);

    emit updated();
}
