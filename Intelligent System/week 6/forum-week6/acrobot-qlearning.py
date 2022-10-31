import gym
import numpy as np
import matplotlib.pyplot as plt
import time
from time import sleep

import warnings
warnings.filterwarnings("ignore", category=DeprecationWarning)

env = gym.make("Acrobot-v1")
print(env.observation_space.low, "\n", env.observation_space.high)


def Qtable(state_space, action_space, bin_size=30):

    bins = [np.linspace(-1, 1, bin_size),
            np.linspace(-1, 1, bin_size),
            np.linspace(-1, 1, bin_size),
            np.linspace(-1, 1, bin_size),
            np.linspace(-12.567, 12.567, bin_size),
            np.linspace(-28.274, 28.274, bin_size)]

    q_table = np.random.uniform(
        low=-1, high=1, size=([bin_size] * state_space + [action_space]))
    return q_table, bins

# discretize the states so that gym can read it


def Discrete(state, bins):
    index = []
    for i in range(len(state)):
        index.append(np.digitize(state[i], bins[i]) - 1)
    return tuple(index)


'''
======
epsilon is associated with how random you take an action.
The epsilon refers to the Exploration vs. Exploitation problem.
Exploration allows the agent to improve current knowledge about the environment by choosing random action.
On the other hand, Exploitation determines the “greedy” action to get the most reward. So the greedy action is picked with the probability of 1-ϵ and random action with ϵ.

gamma = Discount Factor
lr = alpha or learning rate is associated with how big you take a leap
timestep = how often do we want to print the result on the screen
=====
'''


def Q_learning(q_table, bins, episodes=5000, gamma=0.95, lr=0.1, timestep=5000, epsilon=0.2):
    rewards = 0
    solved = False
    steps = 0  # for learning rate
    runs = [0]
    data = {'max': [0], 'avg': [0]}
    start = time.time()
    ep = [i for i in range(0, episodes + 1, timestep)]

    # iterating through n episodes
    for episode in range(1, episodes+1):

        current_state = Discrete(env.reset()[0], bins)  # initial observation
        score = 0
        done = False
        temp_start = time.time()

        while not done:
            steps += 1
            ep_start = time.time()
            if episode % timestep == 0:
                env.render()  # to render the result on the screen

            if np.random.uniform(0, 1) < epsilon:
                # exploration: random action
                action = env.action_space.sample()
            else:
                # exploitation: finding the largest reward
                action = np.argmax(q_table[current_state])

            # print(env.step(action), 'AFJALS;DJFKA;SDF')
            observation, reward, done, _, _ = env.step(action)

            next_state = Discrete(observation, bins)
            # print(observation,next_state)
            # sleep(2)

            score += reward

            # Learning part, updating the q value
            if not done:
                max_future_q = np.max(q_table[next_state])
                current_q = q_table[current_state+(action,)]
                new_q = (1-lr)*current_q + lr*(reward + gamma*max_future_q)
                q_table[current_state+(action,)] = new_q

            current_state = next_state

        # End of the loop update
        else:
            rewards += score
            runs.append(score)
            if score > 195 and steps >= 100 and solved == False:  # considered as a solved:
                solved = True
                print('Solved in episode : {} in time {}'.format(
                    episode, (time.time()-ep_start)))

        # Timestep value update
        if episode % timestep == 0:
            print('Episode : {} | Reward -> {} | Max reward : {} | Time : {}'.format(
                episode, rewards/timestep, max(runs), time.time() - ep_start))
            data['max'].append(max(runs))
            data['avg'].append(rewards/timestep)
            if rewards/timestep >= 195:
                print('Solved in episode : {}'.format(episode))
            rewards, runs = 0, [0]

    # Let's see the result in a line plot
    if len(ep) == len(data['max']):
        plt.plot(ep, data['max'], label='Max')
        plt.plot(ep, data['avg'], label='Avg')
        plt.xlabel('Episode')
        plt.ylabel('Reward')
        plt.legend(loc="upper left")
        plt.show()

    time.sleep(3)
    env.close()


# TRANING
q_table, bins = Qtable(len(env.observation_space.low), env.action_space.n)

Q_learning(q_table, bins, lr=0.15, gamma=0.995,
           episodes=5*10**3, timestep=1000)
