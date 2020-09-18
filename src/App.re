[%bs.raw {|require('./App.css')|}];
// https://developer.mozilla.org/en-US/docs/Web/API/Intersection_Observer_API
type observer = {
  .
  [@bs.meth] "observe": Js.Nullable.t(Dom.element) => unit,
  [@bs.meth] "unobserve": Js.Nullable.t(Dom.element) => unit,
};

type entry = {
  isIntersecting: bool,
  target: Dom.element,
};
type options = {
  root: Js.Nullable.t(string),
  rootMargin: string,
  threshold: int,
};
[@bs.new]
external intersectionObserver: (array(entry) => unit, options) => observer =
  "IntersectionObserver";

open LastLaunchesQuery;

[@react.component]
let make = () => {
  let (launch, setLaunch) = React.useState(() => None);
  let (launches, setLaunches) = React.useState(() => None);
  // let (fetchMoreButton, showFetchMoreButton) = React.useState(() => false);
  let result = LastLaunchesQuery.use({offset: Some(0)});

  let loader = React.useRef(Js.Nullable.null);
  React.useEffect2(
    () => {
      let loadMore = entities => {
        let target = entities[0];
        if (target.isIntersecting && launch == None) {
          let offset =
            switch (result.data) {
            | Some(data) =>
              switch (data.launchesPast) {
              | Some(launchesPast) => Js.Array.length(launchesPast)
              | None => Js.Array.length([||])
              }
            | None => Js.Array.length([||])
            };
          result.fetchMore(~variables={offset: Some(offset)}, ())
          ->Promise.get(
              fun
              | {data: Some({launchesPast}), error: None} => {
                  let launchesPast =
                    launchesPast->Belt.Option.getWithDefault([||]);
                  setLaunches(_ => Some(launchesPast));
                }
              // Js.log2("launchesPast: ", launchesPast);
              | {error} => Js.log2("Error: ", error),
            );
        };
      };
      let options = {
        root: Js.Nullable.undefined,
        rootMargin: "20px",
        threshold: 1,
      };
      let observer = intersectionObserver(loadMore, options);
      if (result.data !== None) {
        observer##observe(loader.current);
      };
      None;
    },
    (result, launch),
  );

  let handleShowDetails: option(string) => unit =
    id => {
      setLaunch(_ => id);
    };
  let hideWhenLaunch = {
    launch->Belt.Option.isSome ? "none" : "";
  };

  <div className="App">
    <h1> "ERU SpaceX Launch Tracker"->React.string </h1>
    {switch (launch) {
     | Some(launch) => <LaunchDetails handleShowDetails id={Some(launch)} />

     | None => React.null
     }}
    <LaunchList
      display=hideWhenLaunch
      handleShowDetails
      launches={launches->Belt.Option.getWithDefault([||])}
    />
    <div ref={ReactDOMRe.Ref.domRef(loader)}> "Load More"->React.string </div>
  </div>;
};
