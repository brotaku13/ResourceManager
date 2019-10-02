import random
import sys
class pcb():
    blocked = 0
    ready = 1
    def __init__(self, ppid, priority):
        self.state = self.ready
        self.parent = ppid
        self.children = [] # int list
        self.resources = [] # (rid, units held)
        self.priority


class rcb():
    def __init__(self, maxInv):
        self.maxInv = maxInv
        self.inv = maxInv
        self.wl = []

class scheduler():
    def __init__(self):
        self.numLevels = 3
        self.wl = [[0], [], []]
        
    def curr_proc(self):
        for i in range(2, -1, -1):
            if self.wl[i]:
                return self.wl[i][0]
        raise Exception('No processes in list')

class manager():
    def __init__(self):
        self.maxProc = 16
        self.plist = [None] * self.maxProc
        self.rlist = [rcb(1), rcb(1), rcb(2), rcb(3)]
        self.scheduler = scheduler()

    def create(self, priority):
        return -1

    def destroy(self, pid):
        return 4

    def release(self, rid, units):
        return 3

    def request(self, rid, untis):
        return 2

    def timeout(self):
        return 1

    def init(self):
        return 0

    def curr_proc(self):
        return self.plist[self.scheduler.curr_proc()]
        

class processor():
    def __init__(self, commandfile, resultfile):
        self.manager = manager()
        self.commandfile = open(commandfile, 'w')
        self.resultfile = open(commandfile, 'w')
        self.commands = [
            self.create, 
            self.destroy, 
            self.timeout, 
            self.release, 
            self.request
        ]

    def write(self, file, line):
        if isinstance(line, list):
            line = ' '.join(map(str, line))
        print(line)
        file.write(line + '\n')

    def create(self):
        p = random.choice([1, 2])
        self.write(self.commandfile, f'cr {p}')
        return self.manager.create(p)

    def destroy(self):
        l = []
        for i, p in enumerate(self.manager.plist):
            if p is not None:
                l.append(i)
        pid = random.choice(l)
        self.write(self.commandfile, f'de {pid}')
        return self.manager.destroy(pid)
        
    def release(self):
        # release random resource current process is holding, if any.
        p = self.manager.curr_proc()
        rid, units = None, None
        found = False
        if len(p.resources) > 0:
            rid, units = random.choice(p.resources)
            found = True
        else:
            rid, units = random.choice([0, 1, 2, 3]), random.choice([1, 2, 3])
        
        # get units to release
        unitsReleased = 0
        if found:
            unitsReleased = random.randint(1, units) # grab units held from second index
        else:
            unitsReleased = random.choice([1, 2, 3])

        self.write(self.commandfile, f'rl {rid} {unitsReleased}')

        return self.manager.release(rid, unitsReleased)

    def request(self):
        # request a resource, if the proc is holding that resource, 
        # then don't request more units than the max
        # else request a resource at a random units

        p = self.manager.curr_proc() 
        # get random resource to request
        r = random.choice([0, 1, 2, 3])
        max_units = self.manager.rlist[r].maxInv
        units_req = 0
        
        resource = list(filter(lambda x: x[0] == r, p.resources))
        # if current process is holding that resource, attempt to request a reasonable amount
        if resource:
            remaining = max_units - resource[0]
            if remaining != 0:
                units_req = random.randint(1, remaining)
            else:
                # we can't request more of this resource, guess we gonna error out
                units_req = random.randint(1, max_units)
        else:
            # resource is not being held, request any number of units in range
            units_req = random.randint(1, max_units)
        
        self.write(self.commandfile, f'rq {r} {units_req}')
        return self.manager.request(r, units_req)

    def init(self):
        self.write(self.commandfile, 'in')
        return self.manager.init()
        
    def timeout(self):
        self.write(self.commandfile, 'to')
        return self.manager.timeout()

    def run(self, iters):
        for i in range(iters):
            response = []
            response.append(self.init())

            # while not return -1, call commands
            while response[-1] != -1:
                command = random.choice(self.commands)
                response.append(command())

            # record results
            self.write(self.resultfile, response)
            response = []

        self.commandfile.close()
        self.resultfile.close()


def main():
    args = sys.argv
    commandfile = args[1]
    results = args[2]
    iters = int(args[3])

    p = processor(commandfile, results)
    p.run(iters)

if __name__ == '__main__':
    main()