-------------------------------- MODULE wire --------------------------------
EXTENDS Integers

(*--algorithm wire
    variables
        people = {"alice", "bob"},
        acc = [p \in people |-> 5],
        sender = "alice",
        receiver = "bob",
        amount \in 1..6;
    
    define
        NoOverdrafts == \A p \in people: acc[p] >= 0
    end define;
    
    process Wire \in 1..2
        variables
            sender = "alice",
            receiver = "bob",
            amount \in 1..acc[sender];
    begin
        CheckFunds:
            if amount <= acc[sender] then
                Withdraw:
                    acc[sender] := acc[sender] - amount;
                Deposit:
                    acc[receiver] := acc[receiver] + amount;
            end if;
    end process;
end algorithm;*)
\* BEGIN TRANSLATION
VARIABLES people, acc, sender, receiver, amount, pc

(* define statement *)
NoOverdrafts == \A p \in people: acc[p] >= 0





vars == << people, acc, sender, receiver, amount, pc >>

Init == (* Global variables *)
        /\ people = {"alice", "bob"}
        /\ acc = [p \in people |-> 5]
        /\ sender = "alice"
        /\ receiver = "bob"
        /\ amount = 3
        /\ pc = "Withdraw"

Withdraw == /\ pc = "Withdraw"
            /\ acc' = [acc EXCEPT ![sender] = acc[sender] - amount]
            /\ pc' = "Deposit"
            /\ UNCHANGED << people, sender, receiver, amount >>

Deposit == /\ pc = "Deposit"
           /\ acc' = [acc EXCEPT ![receiver] = acc[receiver] + amount]
           /\ pc' = "Done"
           /\ UNCHANGED << people, sender, receiver, amount >>

Next == Withdraw \/ Deposit
           \/ (* Disjunct to prevent deadlock on termination *)
              (pc = "Done" /\ UNCHANGED vars)

Spec == Init /\ [][Next]_vars

Termination == <>(pc = "Done")

\* END TRANSLATION

=============================================================================
\* Modification History
\* Last modified Mon Jan 21 09:55:46 EET 2019 by k2
\* Created Mon Dec 31 13:26:27 EET 2018 by k2
