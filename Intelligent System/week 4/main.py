from alphabeta import TicTacToe
from alphabeta import alpha_beta_value


def play(state):
    """Makes turn and prints the result of it until the game is over
    :param state: The initial state of the game (TicTacToe)
    """
    while not state.is_end_state():
        if state.crosses_turn:
            value = -1
            children = state.generate_children()
            state = children[0]
            for child in children:
                new_value = alpha_beta_value(child)
                if new_value > value:
                    value = new_value
                    state = child
        else:
            value = 1
            children = state.generate_children()
            state = children[0]
            for child in children:
                new_value = alpha_beta_value(child)
                if new_value < value:
                    value = new_value
                    state = child
        print(state)

def main():
    """You need to implement the following functions/methods:
    play(state): makes turn and prints the result of it until the game is over
    value() in TicTacToe class: returns the current score of the game
    generate_children() in TicTacToe class: returns a list of all possible states after this turn
    alpha_beta_value(node): implements the MinMax algorithm with alpha-beta pruning
    max_value(node, alpha, beta): implements the MinMax algorithm with alpha-beta pruning
    min_value(node, alpha, beta):implements the MinMax algorithm with alpha-beta pruning
    """
    empty_board = 3 * '???'
    state = TicTacToe(empty_board, True)
    print(state)
    play(state)


if __name__ == '__main__':
    main()
