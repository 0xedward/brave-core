/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import * as bluebird from 'bluebird'
global.Promise = bluebird

function promisifier (method: any) {
  // return a function
  return function promisified (...args: any[]) {
    // which returns a promise
    return new Promise((resolve: any) => {
      args.push(resolve)
      method.apply(this, args)
    })
  }
}

function promisifyAll (obj: object, list: string[]) {
  list.forEach(api => bluebird.promisifyAll(obj[api], { promisifier }))
}

// let chrome extension api support Promise
promisifyAll(chrome, [
  'browserAction',
  'tabs',
  'windows',
  'commands'
])

promisifyAll(chrome.storage, [
  'local'
])

bluebird.promisifyAll(chrome.braveShields, { promisifier })

require('./background/api')
require('./background/events')
require('./background/store')
if (chrome.test) {
  chrome.test.sendMessage('brave-extension-enabled')
}

chrome.commands.onCommand.addListener(function(command) {
  alert(command);
  // check if command === 'toggle-brave-shields'
  // Call chrome.tab.getCurrent() to get current tab
  // Check if current tab !== undefined
  // pass tab into getShieldSettingsForTabData
  // retrieve the braveShields value and pass that into toggleShieldValue
  // Take the return of the toggleShieldValue and pass it into setAllowBraveShields(rv of toggleShieldValue, tab.origin)
})
