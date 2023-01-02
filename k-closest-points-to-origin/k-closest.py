from typing import List
import random


class Solution:
    def find(self, distances, k):
        if len(distances) == k:
            return [point[0] for point in distances]
        randomPoint = random.choice(distances)
        pivot = randomPoint[1]

        i = 0
        left = []
        right = []
        equal = []
        while i < len(distances):
            if distances[i][1] < pivot:
                left.append(distances[i])
            elif distances[i][1] == pivot:
                equal.append(distances[i])
            else:
                right.append(distances[i])
            i += 1

        if len(left) == k:
            return [point[0] for point in left]
        elif len(left) + len(equal) == k:
            return [point[0] for point in left] + [point[0] for point in equal]
        elif k < len(left):
            return self.find(left, k)
        else:
            return [point[0] for point in left + equal] + self.find(
                right, k - len(left) - len(equal)
            )

    def findDistance(self, point):
        return point[0] ** 2 + point[1] ** 2

    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
        distances = [
            (
                point,
                self.findDistance(point),
            )
            for point in points
        ]

        return self.find(distances, k)
