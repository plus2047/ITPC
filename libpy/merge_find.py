class UFSet:
    def __init__(self, n):
        self.root_vec = list(range(n))
    
    def find(self, x):
        if self.root_vec[x] != x:
            self.root_vec[x] = self.find(self.root_vec[x])
        return self.root_vec[x]
    
    def union(self, x, y):
        self.root_vec[self.find(y)] = self.root_vec[self.find(x)]
