EXTENDS Sequences, Integers, TLC, FiniteSets
(*--algorithm recycler
    variables
        capacity = [trash |-> 10, recycle |-> 10],
        bins = [trash |-> {}, recycle |-> {}],
        count = [trash |-> 0, recycle |-> 0],
        items = <<
            [type |-> "recycle", size |-> 5],
            [type |-> "trash", size |-> 5],
            [type |-> "recycle", size |-> 4],
            [type |-> "recycle", size |-> 3]
        >>,
        curr = ""; \* helper: current item
    
    begin
        while items /= <<>> do
            curr := Head(items);
            items := Tail(items);
            if curr.type = "recycle" /\ curr.size < capacity.recycle then
                bins.recycle := bins.recycle \union {curr};
                capacity.recycle := capacity.recycle - curr.size;
                count.recycle := count.recycle + 1;
            elsif curr.size < capacity.trash then
                bins.trash := bins.trash \union {curr};
                capacity.trash := capacity.trash - curr.size;
                count.trash := count.trash + 1;
            end if;
        end while;
        assert capacity.trash >= 0 /\ capacity.recycle >= 0;
        assert Cardinality(bins.trash) = count.trash;
        assert Cardinality(bins.recycle) = count.recycle;
end algorithm; *)