/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/ui/tabs/brave_tab_strip_model.h"

#include <algorithm>
#include <memory>

#include "brave/browser/ui/tabs/mru_tab_cycling_controller.h"
#include "brave/common/pref_names.h"
#include "build/build_config.h"
#include "chrome/browser/profiles/profile.h"
#include "components/prefs/pref_service.h"
#include "content/public/browser/web_contents.h"

BraveTabStripModel::BraveTabStripModel(TabStripModelDelegate* delegate,
                                       Profile* profile)
    : TabStripModel(delegate, profile) {
  mru_tab_cycling_controller_ = std::make_unique<MRUTabCyclingController>(this);
}

BraveTabStripModel::~BraveTabStripModel() {}

void BraveTabStripModel::SelectRelativeTab(bool forward,
                                           UserGestureDetails detail) {
  if (contents_data_.empty())
    return;

  bool is_mru_enabled = profile()->GetPrefs()->GetBoolean(kMRUCyclingEnabled);

  if (is_mru_enabled) {
    SelectMRUTab(forward, detail);
  } else {
    TabStripModel::SelectRelativeTab(forward, detail);
  }
}

void BraveTabStripModel::SelectMRUTab(bool forward, UserGestureDetails detail) {
  if (mru_cycle_list_.empty()) {
    // Start cycling

    // Create a list of tab indexes sorted by time of last activation
    for (int i = 0; i < count(); ++i) {
      mru_cycle_list_.push_back(i);
    }

    std::sort(mru_cycle_list_.begin(), mru_cycle_list_.end(),
              [this](int a, int b) {
                return GetWebContentsAt(a)->GetLastActiveTime() >
                       GetWebContentsAt(b)->GetLastActiveTime();
              });

    // Tell the cycling controller that we start cycling to handle tabs keys
    mru_tab_cycling_controller_->StartMRUCycling();
  }

  if (forward) {
    std::rotate(mru_cycle_list_.begin(),
                mru_cycle_list_.begin() + 1,
                mru_cycle_list_.end());
  } else {
    std::rotate(mru_cycle_list_.rbegin(),
                mru_cycle_list_.rbegin() + 1,
                mru_cycle_list_.rend());
  }

  ActivateTabAt(mru_cycle_list_[0], detail);
}

void BraveTabStripModel::StopMRUCycling() {
  mru_cycle_list_.clear();
}
