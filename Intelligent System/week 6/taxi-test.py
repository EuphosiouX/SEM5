import gym
import numpy as np
import matplotlib.pyplot as plt
import time
from time import sleep

import warnings
warnings.filterwarnings("ignore", category=DeprecationWarning)

env = gym.make("Taxi-v3")

# initialize q-table
state_size = env.observation_space.n
action_size = env.action_space.n
qtable = np.zeros((state_size, action_size))

# hyperparameters
learning_rate = 0.9
discount_rate = 0.8
epsilon = 1.0
decay_rate = 0.005

# training variables
episodes = 5000
max_steps = 99  # per episode
timestep = 1000

rewards = 0
solved = False
steps = 0  # for learning rate
runs = [0]
data = {'max': [0], 'avg': [0]}
start = time.time()
ep = [i for i in range(0, episodes + 1, timestep)]

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

# iterating through n episodes
for episode in range(1, episodes+1):

    state = env.reset()[0]  # initial observation
    score = 0
    done = False
    temp_start = time.time()

    while not done:
        steps += 1
        ep_start = time.time()

        if np.random.uniform(0, 1) < epsilon:
            # exploration: random action
            action = env.action_space.sample()
        else:
            # exploitation: finding the largest reward
            action = np.argmax(q_table[current_state])

        # print(env.step(action), 'AFJALS;DJFKA;SDF')
        new_state, reward, done, _, _ = env.step(action)

        score += reward

        # Learning part, updating the q value
        if not done:
            qtable[state, action] = qtable[state, action] + learning_rate * \
                (reward + discount_rate *
                 np.max(qtable[new_state, :])-qtable[state, action])

        state = new_state

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

env.close()
