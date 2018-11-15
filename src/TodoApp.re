type state = {
  items: list(SharedTypes.item)
};

type action =
  | AddItem
  | ToggleItem(int)

let component = ReasonReact.reducerComponent("TodoApp");

let lastId = ref(0);

let newItem = (): SharedTypes.item => {
  lastId := lastId^ + 1;
  { id: lastId^, title: "Click a button", completed: true };
};

let make = (_) => {
  ...component,

  initialState: (): state => {
    items: [
      { id: 0, title: "Write some things to do", completed: false }
    ]
  },

  reducer: (action, { items }) =>
    switch action {
    | AddItem => ReasonReact.Update({ items: [newItem(), ...items] })
    | ToggleItem(id) =>
      let items = List.map(
        (item: SharedTypes.item) =>
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
        (
          items
          |> List.map((item: SharedTypes.item) =>
              <TodoItem
                key=(string_of_int(item.id))
                onToggle=(_ => self.send(ToggleItem(item.id)))
                item
              />
            )
          |> Array.of_list
          |> ReasonReact.array
        )
      </div>
      <div>
        (ReasonReact.string(string_of_int(numItems) ++ " items"))
      </div>
    </div>
  }
};
