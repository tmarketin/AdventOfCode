import numpy as np
import itertools

from copy import deepcopy

def simulate_battle(plr, boss, verbose):
    turn = 1
    while(plr['hp'] > 0 and boss['hp'] > 0):
        if(verbose):
            print("Turn ",turn)
        dmg_dealt = plr['dmg'] - boss['armor']
        if(dmg_dealt < 1):
            dmg_dealt = 1
        boss['hp'] = boss['hp'] - dmg_dealt
        if(verbose):
            print("Player deals ",dmg_dealt," damage, boss at ",boss['hp']," hit points.")
        if(boss['hp'] <= 0):
            return "Player wins!"

        dmg_dealt = boss['dmg'] - plr['armor']
        if(dmg_dealt < 1):
            dmg_dealt = 1
        plr['hp'] = plr['hp'] - dmg_dealt
        if(verbose):
            print("Boss deals ",dmg_dealt," damage, player at ",plr['hp']," hit points.")
        if(plr['hp'] <= 0):
            return "Boss wins!"

        turn = turn + 1
    return

def gen_items_dict(items_txt):
    items = []
    for line in items_txt.splitlines():
        data_dict = {}
        l = line.split()
        data_dict['cost'] = int(l[1])
        data_dict['dmg'] = int(l[2])
        data_dict['armor'] = int(l[3])
        items.append([l[0],data_dict])
    
    return items

def gen_character(plr_input, items_list):
    plr = deepcopy(plr_input)
    for item in items_list:
        plr['dmg'] = plr['dmg'] + item[1]['dmg']
        plr['armor'] = plr['armor'] + item[1]['armor']
        plr['cost'] = plr['cost'] + item[1]['cost']
        plr['items_list'].append(item[0])
    
    return plr

boss_init = {'hp': 104, 'dmg': 8, 'armor': 1}
player_empty = {'hp': 100, 'dmg': 0, 'armor': 0, 'cost': 0, 'items_list': []}

weapons_txt = """Dagger        8     4       0
Shortsword   10     5       0
Warhammer    25     6       0
Longsword    40     7       0
Greataxe     74     8       0"""

armor_txt = """NoArmor  0   0   0
Leather      13     0       1
Chainmail    31     0       2
Splintmail   53     0       3
Bandedmail   75     0       4
Platemail   102     0       5"""

rings_txt = """Damage+1    25     1       0
Damage+2    50     2       0
Damage+3   100     3       0
Defense+1   20     0       1
Defense+2   40     0       2
Defense+3   80     0       3"""

weapons = gen_items_dict(weapons_txt)
armor = gen_items_dict(armor_txt)
rings = gen_items_dict(rings_txt)

cost_min = 500
items_min = []
cost_max = 0
items_max = []
for weapon_item in weapons:
    for armor_item in armor:
        # no rings
        item_list = []
        item_list.append(weapon_item)
        item_list.append(armor_item)
        plr = gen_character(player_empty, item_list)
        boss = dict(boss_init)
        cost = plr['cost']
        res = simulate_battle(plr, boss, False)
        if(res == "Player wins!" and cost < cost_min):
            items_min = item_list
            cost_min = cost
        if(res == "Boss wins!" and cost > cost_max):
            items_max = item_list
            cost_max = cost

        # one ring
        for ring in rings:
            item_list = []
            item_list.append(weapon_item)
            item_list.append(armor_item)
            item_list.append(ring)
            plr = gen_character(player_empty, item_list)
            boss = dict(boss_init)
            cost = plr['cost']
            res = simulate_battle(plr, boss, False)
            if(res == "Player wins!" and cost < cost_min):
                items_min = item_list
                cost_min = cost
            if(res == "Boss wins!" and cost > cost_max):
                items_max = item_list
                cost_max = cost
            
        # two rings
        permutations = list(itertools.permutations(rings,2))
        for perm in permutations:
            item_list = []
            item_list.append(weapon_item)
            item_list.append(armor_item)
            item_list.append(perm[0])
            item_list.append(perm[1])
            plr = gen_character(player_empty,item_list)
            boss = dict(boss_init)
            cost = plr['cost']
            res = simulate_battle(plr, boss, False)
            if(res == "Player wins!" and cost < cost_min):
                items_min = item_list
                cost_min = cost
            if(res == "Boss wins!" and cost > cost_max):
                items_max = item_list
                cost_max = cost

print(items_min, cost_min)
print(items_max, cost_max)