/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */
/* global jest */

import { getMockChrome } from './testData'

global.window = {}

window.localStorage = {
  getItem: jest.fn(),
  setItem: jest.fn()
}

window.location = {
  search: '?testTorrentId'
}

window.decodeURIComponent = (any) => 'test'

// This mocks rAF to avoid React console.error
// while running Jest tests
global.requestAnimationFrame = function (cb) {
  return setTimeout(cb, 0)
}

if (global.chrome === undefined) {
  global.chrome = getMockChrome()
}
