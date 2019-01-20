-------------------------------- MODULE wire --------------------------------
EXTENDS Integers
(*--algorithm wire
begin
    variables
        people = {"alice", "bob"},
        acc = [p \in people |-> 5],
        sender = "alice",
        receiver = "bob",
        amount = 3;
    define
        NoOverdrafts == \A p \in people: acc[p] >= 0
    end define;
end algorithm;*)

=============================================================================
\* Modification History
\* Last modified Mon Jan 07 06:24:09 EET 2019 by k2
\* Created Mon Dec 31 13:26:27 EET 2018 by k2
