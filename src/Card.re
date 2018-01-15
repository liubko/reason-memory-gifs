[%bs.raw {|require('./Card.css')|}];

let component = ReasonReact.statelessComponent("Card");

let make = (~data: Records.card, ~isSelected=false, ~onClick, _children) => {
  ...component,
  render: _self =>
    <div
      className=(
        Cn.make([
          "Card",
          "isSelected" |> Cn.ifBool(isSelected),
          "isGuesed" |> Cn.ifBool(data.isGuesed)
        ])
      )
      onClick=(_evt => isSelected || data.isGuesed ? () : onClick())>
      <div className="Card-flipper">
        <div className="Card-front">
          (ReasonReact.stringToElement("front"))
        </div>
        <div className="Card-back">
          <img
            src="https://media3.giphy.com/media/l0ExiaIdNnxoEz2s8/200.webp#0-grid1"
          />
          <p className="title"> (ReasonReact.stringToElement(data.value)) </p>
        </div>
      </div>
    </div>
};