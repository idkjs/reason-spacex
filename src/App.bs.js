// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var $$Promise = require("reason-promise/src/js/promise.js");
var Caml_array = require("bs-platform/lib/js/caml_array.js");
var LaunchList = require("./components/LaunchList/LaunchList.bs.js");
var Belt_Option = require("bs-platform/lib/js/belt_Option.js");
var LaunchDetails = require("./components/LaunchDetails/LaunchDetails.bs.js");
var LastLaunchesQuery = require("./components/LaunchList/LastLaunchesQuery.bs.js");

((require('./App.css')));

function App(Props) {
  var match = React.useState(function () {
        
      });
  var setLaunch = match[1];
  var launch = match[0];
  var match$1 = React.useState(function () {
        
      });
  var setLaunches = match$1[1];
  var result = Curry.app(LastLaunchesQuery.LastLaunchesQuery.use, [
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        undefined,
        {
          offset: 0
        }
      ]);
  var loader = React.useRef(null);
  React.useEffect((function () {
          var loadMore = function (entities) {
            var target = Caml_array.caml_array_get(entities, 0);
            if (!(target.isIntersecting && launch === undefined)) {
              return ;
            }
            var data = result.data;
            var offset;
            if (data !== undefined) {
              var launchesPast = data.launchesPast;
              offset = launchesPast !== undefined ? launchesPast.length : [].length;
            } else {
              offset = [].length;
            }
            return $$Promise.get(Curry._5(result.fetchMore, undefined, undefined, {
                            offset: offset
                          }, undefined, undefined), (function (param) {
                          var match = param.data;
                          if (match !== undefined) {
                            if (param.error !== undefined) {
                              console.log("Error: ", param.error);
                              return ;
                            }
                            var launchesPast = Belt_Option.getWithDefault(match.launchesPast, []);
                            return Curry._1(setLaunches, (function (param) {
                                          return launchesPast;
                                        }));
                          }
                          console.log("Error: ", param.error);
                          
                        }));
          };
          var options = {
            root: undefined,
            rootMargin: "20px",
            threshold: 1
          };
          var observer = new IntersectionObserver(loadMore, options);
          if (result.data !== undefined) {
            observer.observe(loader.current);
          }
          
        }), [
        result,
        launch
      ]);
  var handleShowDetails = function (id) {
    return Curry._1(setLaunch, (function (param) {
                  return id;
                }));
  };
  var hideWhenLaunch = Belt_Option.isSome(launch) ? "none" : "";
  return React.createElement("div", {
              className: "App"
            }, React.createElement("h1", undefined, "ERU SpaceX Launch Tracker"), launch !== undefined ? React.createElement(LaunchDetails.make, {
                    id: launch,
                    handleShowDetails: handleShowDetails
                  }) : null, React.createElement(LaunchList.make, {
                  launches: Belt_Option.getWithDefault(match$1[0], []),
                  handleShowDetails: handleShowDetails,
                  display: hideWhenLaunch
                }), React.createElement("div", {
                  ref: loader
                }, "Load More"));
}

var make = App;

exports.make = make;
/*  Not a pure module */
