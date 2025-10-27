(() => {
  var __create = Object.create;
  var __defProp = Object.defineProperty;
  var __getOwnPropDesc = Object.getOwnPropertyDescriptor;
  var __getOwnPropNames = Object.getOwnPropertyNames;
  var __getProtoOf = Object.getPrototypeOf;
  var __hasOwnProp = Object.prototype.hasOwnProperty;
  var __commonJS = (cb, mod) => function __require() {
    return mod || (0, cb[__getOwnPropNames(cb)[0]])((mod = { exports: {} }).exports, mod), mod.exports;
  };
  var __copyProps = (to, from, except, desc) => {
    if (from && typeof from === "object" || typeof from === "function") {
      for (let key of __getOwnPropNames(from))
        if (!__hasOwnProp.call(to, key) && key !== except)
          __defProp(to, key, { get: () => from[key], enumerable: !(desc = __getOwnPropDesc(from, key)) || desc.enumerable });
    }
    return to;
  };
  var __toESM = (mod, isNodeMode, target) => (target = mod != null ? __create(__getProtoOf(mod)) : {}, __copyProps(
    // If the importer is in node compatibility mode or this is not an ESM
    // file that has been converted to a CommonJS file using a Babel-
    // compatible transform (i.e. "__esModule" has not been set), then set
    // "default" to the CommonJS "module.exports" for node compatibility.
    isNodeMode || !mod || !mod.__esModule ? __defProp(target, "default", { value: mod, enumerable: true }) : target,
    mod
  ));

  // www/node_modules/pp-is/dist/pp-is.min.js
  var require_pp_is_min = __commonJS({
    "www/node_modules/pp-is/dist/pp-is.min.js"(exports, module) {
      !(function(e, t) {
        "object" == typeof exports && "undefined" != typeof module ? module.exports = t() : "function" == typeof define && define.amd ? define(t) : (e = "undefined" != typeof globalThis ? globalThis : e || self).ppIs = t();
      })(exports, (function() {
        "use strict";
        const e = (e2, t2) => ((e3) => Object.prototype.toString.call(e3))(e2) === "[object " + t2 + "]", t = (t2) => e(t2, "String"), i = (t2) => e(t2, "Array"), o = (t2) => e(t2, "Object"), s = (t2) => true === t2 || false === t2 || e(t2, "Boolean"), n = (t2) => e(t2, "Function"), d = (t2) => e(t2, "Undefined"), l = (t2) => e(t2, "Null"), r = (e2) => Number.isNaN(Number.parseInt(e2)), a = (e2, t2, i2) => {
          const o2 = e2(t2);
          return s(o2) ? o2 : i2;
        }, p = (e2) => (t2, i2, o2) => ((e3, t3, i3, o3) => {
          const s2 = e3(t3);
          return s2 ? !n(i3) || a(i3, t3, s2) : !!n(o3) && a(o3, t3, s2);
        })(e2, t2, i2, o2);
        return { isArray: p(i), isBoolean: p(s), isDate: p(((t2) => e(t2, "Date"))), isElement: p(((e2) => !(!e2 || 1 !== e2.nodeType))), isEmpty: p(((e2) => t(e2) ? "" === e2 : i(e2) ? 0 == e2.length : !o(e2) || 0 === Object.keys(e2).length)), isBlank: p(((e2) => !!t(e2) && ("" === e2 || "" === e2.trim()))), isFunction: p(n), isNull: p(l), isNumber: p(((t2) => e(t2, "Number") && !r(t2))), isObject: p(o), isString: p(t), isUndefined: p(d), isNil: p(((e2) => d(e2) || l(e2))), isEmail: p(((e2) => /^([a-z1-9\._-]+)@([a-z0-9-]+\.[a-z]{2,11}|[a-z0-9]+\.[a-z]{2,24}\.[a-z]{2,24})$/i.test(e2))), isNaN: p(r), isRegExp: p(((t2) => e(t2, "RegExp"))), isUrl: p(((e2) => /^(https?:\/\/)?([w]{3}\.|[w]{3}2\.)?([a-z\d]+\.)?([a-z\d]+\.[a-z]{2,}|localhost|[\d]+\.[\d]+\.[\d]+\.[\d]+)(\:[\d]+)?([\??\/?]+[\/;&a-z\d%_.~+=-]*)?(\#[\/;&a-z\d%_.~+=-]*)?$/gi.test(e2))), isNodeList: p(((e2) => "undefined" != typeof NodeList && NodeList.prototype.isPrototypeOf(e2))), isHTMLCollection: p(((e2) => "undefined" != typeof HTMLCollection && HTMLCollection.prototype.isPrototypeOf(e2))), isPromise: p(((t2) => e(t2, "Promise"))) };
      }));
    }
  });

  // www/node_modules/pp-events/dist/pp-events.min.js
  var require_pp_events_min = __commonJS({
    "www/node_modules/pp-events/dist/pp-events.min.js"(exports, module) {
      !(function(e, n) {
        "object" == typeof exports && "undefined" != typeof module ? module.exports = n(require_pp_is_min()) : "function" == typeof define && define.amd ? define(["pp-is"], n) : (e = "undefined" != typeof globalThis ? globalThis : e || self).ppEvents = n(e.ppIs);
      })(exports, (function(e) {
        "use strict";
        return function n(i) {
          var t = this;
          if (!(t instanceof n)) return new n(i);
          t.events = {}, t.checkOn = (n2) => e.isString(n2, ((e2) => Object.hasOwnProperty.call(t.events, e2))), t.on = (n2, i2) => {
            e.isString(n2, ((n3) => {
              e.isFunction(i2, ((i3) => {
                let s = t.events;
                e.isUndefined(s[n3], (() => {
                  s[n3] = [i3];
                }), (() => {
                  s[n3].push(i3);
                }));
              }));
            }));
          }, t.emit = (n2, ...i2) => {
            e.isString(n2, ((n3) => {
              e.isArray(t.events[n3], ((e2) => {
                for (const n4 of e2.slice()) n4.apply(t, i2);
              }));
            }));
          }, t.removeListener = (n2, i2) => {
            e.isString(n2, ((n3) => {
              e.isArray(t.events[n3], ((e2) => {
                const n4 = e2.indexOf(i2);
                n4 > -1 && e2.splice(n4, 1);
              }));
            }));
          }, e.isObject(i, (() => {
            for (const e2 in i) t.on(e2, i[e2]);
          }));
        };
      }));
    }
  });

  // www/dist/index.js
  var import_pp_is = __toESM(require_pp_is_min());
  var import_pp_events = __toESM(require_pp_events_min());
  var myEvent = (0, import_pp_events.default)({
    "myCustom": function(msg) {
      console.log("mensaje ....", (0, import_pp_is.isArray)(msg));
    }
  });
  myEvent.emit("myCustom", "aaaa");
})();
