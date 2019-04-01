import random
import string

# quick methods to print out random studentIDs and names. Also print out random points for random rounds for the same IDs


def randomString(idlen, fnamelen, lnamelen, ids):
    """Generate a random string of fixed length """
    a = 'A'
    id = string.digits
    fname = string.ascii_lowercase
    lname = string.ascii_lowercase
    frand = ''.join(random.choice(fname) for i in range(fnamelen))
    lrand = ''.join(random.choice(lname) for i in range(lnamelen))
    idrand = ''.join(random.choice(id) for i in range(idlen))
    ids.append(idrand)
    print(a+" "+idrand+" "+frand+" "+lrand)


tarray = []


for i in range(50):
    randomString(6, 7, 7, tarray)

# print(tarray)


def update(idt):
    u = 'U'
    points = '123456789'
    round = '123456'

    for i in range(len(idt)):
        r = ''.join(random.choice(round))
        p = ''.join(random.choice(points))

        print(u+" "+idt[i]+" "+r+" "+p)


update(tarray)
