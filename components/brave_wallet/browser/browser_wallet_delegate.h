/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_WALLET_BROWSER_BROWSER_WALLET_DELEGATE_H_
#define BRAVE_COMPONENTS_BRAVE_WALLET_BROWSER_BROWSER_WALLET_DELEGATE_H_

class BrowserWalletDelegate {
 public:
  virtual ~BrowserWalletDelegate() = default;
  virtual void CloseTabsAndRestart() = 0;
};

#endif  // BRAVE_COMPONENTS_BRAVE_WALLET_BROWSER_BROWSER_WALLET_DELEGATE_H_
