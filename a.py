from micromlgen import port
from sklearn.svm import SVC
from sklearn.preprocessing import Normalizer
from sklearn.metrics import accuracy_score
# from sklearn.datasets import load_iris

if __name__ == '__main__':
    import csv

    # with open('detect.csv', newline='') as csvfile:
    #     data = list(csv.reader(csvfile))

    # # print(data)
    # with open('nodetect.csv', newline='') as csvfile:
    #     data2 = list(csv.reader(csvfile))
    import random
    data = []
    d1 = []
    d2 = []
    d3 = []
    d4 = []
    d5 = []
    for i in range(0, 5):
        d1.append(round(random.uniform(0, 0.31), 3))
        d2.append(round(random.uniform(0, 0.31), 3))
        d3.append(round(random.uniform(0, 0.31), 3))
        d4.append(round(random.uniform(0, 0.31), 3))
        d5.append(round(random.uniform(0, 0.31), 3))
    data = [d1,d2,d3,d4,d5]

    data2 = []
    d1 = []
    d2 = []
    d3 = []
    d4 = []
    d5 = []
    for i in range(0, 5):
        d1.append(round(random.uniform(0.32, 1), 3))
        d2.append(round(random.uniform(0.32, 1), 3))
        d3.append(round(random.uniform(0.32, 1), 3))
        d4.append(round(random.uniform(0.32, 1), 3))
        d5.append(round(random.uniform(0.32, 1), 3))
    data2 = [d1,d2,d3,d4,d5]
    # for i in data[:50]:
    #     i[0] = int(i[0])
        
    # max1 = max(data[:50])
    # min1 = min(data[:50])

    # d1 = []
    # for i in data[:50]:
    #     d1.append([(i[0]-min1[0])/(max1[0]-min1[0])])

    # for i in data2[:50]:
    #     i[0] = int(i[0])
    
    # max2 = max(data2[:50])
    # min2 = min(data2[:50])
    # # print(max2)
    # # print(min2)
    # d2 = []
    # for i in data2[:50]:
    #     d2.append([(i[0]-min2[0])/(max2[0]-min2[0])])
    # print(d1)
    # print(d2)
    
    X = data+data2
    # print(X)
    # print(data)

    y = [0,0,0,0,0,1,1,1,1,1]
    # y = [0] * (50)
    # for i in range(0,25):
    #     y[i] = 0
    # for i in range(25,50):
    #     y[i] = 1

    minss = Normalizer()
    clf = SVC(C=1.0,kernel='poly',gamma = 0.00005).fit(X, y)
    # print(port(clf))
    tyo = [[0.2,0.13,0.10,0.32,0.30]]
    # testing1 = minss.fit_transform(tyo)
    prediction = clf.predict(tyo)
    print(tyo)
    print(prediction)
    print(clf.score(X,y)*100)
    
    