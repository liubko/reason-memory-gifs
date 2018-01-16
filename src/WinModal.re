[%bs.raw {|require('./Card.css')|}];

let component = ReasonReact.statelessComponent("Card");

let make = (~isOpen=false, ~onPlayAgain, _children) => {
  ...component,
  render: _self =>
    <div className=(Cn.make(["modal", "is-active" |> Cn.ifBool(isOpen)]))>
      <div className="modal-background" />
      <div className="modal-content">
        <div className="card">
          <div className="card-content">
            <p className="title">
              (ReasonReact.stringToElement("Congratulations, you win!"))
            </p>
            <p className="subtitle">
              (ReasonReact.stringToElement("TODO: Plase WINN giff here"))
            </p>
          </div>
          <footer className="card-footer">
            <p className="card-footer-item" onClick=onPlayAgain>
              <span> (ReasonReact.stringToElement("Play again")) </span>
            </p>
          </footer>
        </div>
      </div>
    </div>
};