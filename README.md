This is a binary Node.js binding to a small subset of libzonecfg on
illumos/SmartOS. It uses N-API, which IIUC was added to node in v6.

## Install / Build

    npm install

## API

TODO

## See Also

- [node-zutil](https://github.com/joyent/node-zutil) has bindings for some
  of libzonecfg and libzone (?, at least for /usr/include/zone.h) on
  illumos/SmartOS. However, it uses waf and supports node 0.6 and node 0.8
  only (with a patch floating around in orlandov/node-zutil for node 0.10
  support).
