let component = ReasonReact.statelessComponent("TodoItem");

let make = (~item: SharedTypes.item, ~onToggle, _) => {
  ...component,

  render: _ =>
    <div
      className="item"
      onClick=(_ => onToggle())
    >
      <input
        type_="checkbox"
        checked=(item.completed)
      />
      (ReasonReact.string(item.title))
    </div>
};
