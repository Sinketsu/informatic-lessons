program example;

uses
  System.SysUtils, Graph, system.Generics.Collections, system.generics.defaults;

var
  G : TGraph;
  s : TArray<system.integer>;
  i : integer;
  count : integer;
begin
  G := TGraph.Create(6);
  G.add_link(1, 5);
  G.add_link(3, 4);
  G.add_link(1, 2);
  s := G.topological_sort.ToArray;
  for i := G.get_vertex_count - 1 downto 0 do
  begin
    write(s[i], ' ');
  end;
  writeln('');

  count := G.get_linked_components_count;
  writeln(count);

  readln(i);
end.
