open Network_testbed.Test
let () = print_endline "Hello, World!";
let cs = Cstruct.create 9 in 
get_dummy (Cstruct.to_bigarray cs) 
|> function 
  | _ -> get_dummy_t_second cs |> Cstruct.to_string |> Printf.printf "RESULT = %s\n"