type item = {
  id: int,
  title: string,
  completed: bool
};

module TodoItem = {
  let component = ReasonReact.statelessComponent("TodoItem");
  let make = (~item, ~onToggle, _) => {
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
};

type state = {
  items: list(item)
};

type action =
  | AddItem
  | ToggleItem(int)

let component = ReasonReact.reducerComponent("TodoApp");

let lastId = ref(0);

let newItem = () => {
  lastId := lastId^ + 1;
  { id: lastId^, title: "Click a button", completed: true };
};

let toggleItem = (items, id) =>
  List.map(
    item => item.id === id ? { ...item, completed: !item.completed } : item,
    items
  );

let make = (_) => {
  ...component,

  initialState: () => {
    items: [
      { id: 0, title: "Write some things to do", completed: false }
    ]
  },

  reducer: (action, { items }) =>
    switch action {
    | AddItem => ReasonReact.Update({ items: [newItem(), ...items] })
    | ToggleItem(id) =>
      let items = List.map(
        item =>
          item.id === id ? { ...item, completed: !item.completed } : item,
        items
      );
      ReasonReact.Update({ items: items });
    },

  render: self => {
    let { items } = self.state;
    let numItems = List.length(items);
    <div className="app">
      <div className="title">
        (ReasonReact.string("What to do"))
        <button
          onClick=(_ => self.send(AddItem))
        >
          (ReasonReact.string("Add something"))
        </button>
      </div>
      <div className="items">
        (ReasonReact.array(
          Array.of_list(
            List.map(
              item =>
                <TodoItem
                  key=(string_of_int(item.id))
                  onToggle=(_ => self.send(ToggleItem(item.id)))
                  item
                />,
              items
            )
          )
        ))
      </div>
      <div>
        (ReasonReact.string(string_of_int(numItems) ++ " items"))
      </div>
    </div>
  }
};
