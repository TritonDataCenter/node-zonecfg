//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright 2019 Joyent, Inc.
//

//
// Dev Notes:
// - I generally try to follow guidelines describe at
//   https://github.com/joyent/rfd/blob/master/rfd/0139/README.md#guidelines-for-using-node-tap-in-triton-repos
//

var exec = require('child_process').exec;
var test = require('tap').test;

var zonecfg = require('../');


test('zonecfg', function (suite) {
    var currZoneName;

    suite.test('setup: get current zonename', function (t) {
        exec('zonename', function (err, stdout, stderr) {
            t.error(err);
            t.notOk(stderr);
            currZoneName = stdout.trim();
            t.end();
        });
    });

    suite.test('error cases', function (t) {
        t.throws(function () { zonecfg.zone_get_state_str('one', 'two'); },
            /incorrect number of arguments/);
        t.throws(function () { zonecfg.zone_get_state_str('nosuchzone'); },
            /could not get zone "nosuchzone" state: No such zone configured/);
        t.end();
    });

    suite.test('zone_get_state / zone_state_str', function (t) {
        var state = zonecfg.zone_get_state(currZoneName);
        var stateStr = zonecfg.zone_state_str(state);
        t.equal(stateStr, 'running');
        t.end();
    });

    suite.test('zone_get_state_str', function (t) {
        var stateStr = zonecfg.zone_get_state_str(currZoneName);
        t.equal(stateStr, 'running');
        t.end();
    });

    suite.end();
});
