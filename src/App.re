[%bs.raw {| require('./App.css') |}];

type state = {
  data: list(Records.card),
  selected: list(Records.card),
  isGameOver: bool
};

type action =
  | InitGame
  | Select(Records.card)
  | Validate;

let component = ReasonReact.reducerComponent("App");

let dummyData: list(Records.card) = [
  {id: "1", value: "a", isGuesed: false},
  {id: "2", value: "a", isGuesed: false}
  /* {id: "3", value: "b", isGuesed: false},
     {id: "4", value: "c", isGuesed: false},
     {id: "5", value: "b", isGuesed: false},
     {id: "6", value: "c", isGuesed: false},
     {id: "7", value: "d", isGuesed: false},
     {id: "8", value: "e", isGuesed: false},
     {id: "9", value: "f", isGuesed: false},
     {id: "10", value: "d", isGuesed: false},
     {id: "11", value: "e", isGuesed: false},
     {id: "12", value: "f", isGuesed: false} */
];

let make = _children => {
  ...component,
  initialState: () => {data: [], selected: [], isGameOver: false},
  reducer: (action, state) =>
    switch action {
    | InitGame =>
      ReasonReact.Update({data: dummyData, selected: [], isGameOver: false})
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
    self.send(InitGame);
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
            onPlayAgain=(_evt => self.send(InitGame))
          />
          cards
        </div>
      </section>
    </div>;
  }
};