- init:
    run: rm -f cardgame
    blocker: true

- build:
    run: g++ -std=c++0x -Wall -Wextra -Werror main.cpp -o cardgame  # timeout: 1
    blocker: true

- case0:
   run: ./cardgame input.txt
   points: 20
   script:
        - expect: "[ \r\n]*2[ \r\n]*"  # timeout: 1
        - expect: _EOF_  # timeout: 1
   return: 0


- case1_table_out:
   run: ./cardgame input_table_out.txt
   points: 20
   script:
        - expect: "[ \r\n]*3[ \r\n]*"  # timeout: 1
        - expect: _EOF_  # timeout: 1
   return: 0
   

- case2_player1_out:
   run: ./cardgame input_player1_out.txt
   points: 20
   script:
        - expect: "[ \r\n]*0[ \r\n]*"  # timeout: 1
        - expect: _EOF_  # timeout: 1
   return: 0
   

- case3_player2_out:
   run: ./cardgame input_player2_out.txt
   points: 20
   script:
        - expect: "[ \r\n]*2[ \r\n]*"  # timeout: 1
        - expect: _EOF_  # timeout: 1
   return: 0
   

- case4_extraordinary:
   run: ./cardgame input_extraordinary.txt
   points: 20
   script:
        - expect: "[ \r\n]*172[ \r\n]*"  # timeout: 1
        - expect: _EOF_  # timeout: 1
   return: 0
   
