[%bs.raw {| require('./App.css') |}];

type state = {
  data: list(Records.card),
  selected: list(Records.card),
  isGameOver: bool
};

type action =
  | Loaded(list(Records.card))
  | Select(Records.card)
  | Validate;

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => {data: [], selected: [], isGameOver: false},
  reducer: (action, state) =>
    switch action {
    | Loaded(data) =>
      ReasonReact.Update({data, selected: [], isGameOver: false})
    | Select(card) =>
      let length = List.length(state.selected);
      switch length {
      | 1 =>
        ReasonReact.UpdateWithSideEffects(
          {...state, selected: [card, ...state.selected]},
          (
            self =>
              /* 500ms to play animation */
              ignore(Js.Global.setTimeout(() => self.send(Validate), 500))
          )
        )
      | _ => ReasonReact.Update({...state, selected: [card]})
      };
    | Validate =>
      let cardA = List.nth(state.selected, 0);
      let cardB = List.nth(state.selected, 1);
      if (cardA.value === cardB.value) {
        let newData =
          List.map(
            (card: Records.card) => {
              ...card,
              isGuesed:
                card.isGuesed || card.id === cardA.id || card.id === cardB.id
            },
            state.data
          );
        let isGameOver =
          List.for_all((card: Records.card) => card.isGuesed, newData);
        ReasonReact.Update({data: newData, selected: [], isGameOver});
      } else {
        ReasonReact.Update({...state, selected: []});
      };
    },
  didMount: self => {
    let handleGIFsLoaded = self.reduce(gifData => Loaded(gifData));
    GiphyApi.fetchGifs()
    |> Js.Promise.then_(repoData => {
         handleGIFsLoaded(repoData);
         Js.Promise.resolve();
       })
    |> ignore;
    ReasonReact.NoUpdate;
  },
  render: self => {
    let cards =
      ReasonReact.arrayToElement(
        Array.of_list(
          List.map(
            (cardItem: Records.card) =>
              <Card
                key=cardItem.id
                data=cardItem
                onClick=(_evt => self.send(Select(cardItem)))
                isSelected=(
                  List.exists(
                    (item: Records.card) => item.id === cardItem.id,
                    self.state.selected
                  )
                )
              />,
            self.state.data
          )
        )
      );
    <div className="App">
      <section className="App-header hero is-medium is-dark is-bold">
        <div className="hero-body">
          <div className="container">
            <h1 className="title">
              (ReasonReact.stringToElement("reason-memory-gifs"))
            </h1>
            <h2 className="subtitle">
              (ReasonReact.stringToElement("Primary bold subtitle"))
            </h2>
          </div>
        </div>
      </section>
      <section className="App-board section">
        <div className="container">
          <WinModal
            isOpen=self.state.isGameOver
            onPlayAgain=(
              _evt =>
                /* todo: */
                /* self.send(Loaded) */
                ()
            )
          />
          cards
        </div>
      </section>
    </div>;
  }
};