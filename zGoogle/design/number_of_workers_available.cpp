/*
You are given a list of worker shifts, where each shift is
represented as a list [name, start, end]. The name is a string
representing the worker's name, start is an integer representing the
start time of the shift, and end is an integer representing the end
time of the shift. The goal is to generate a schedule that shows the
intervals of time and the workers present during each interval.

Example:
Given the input:
[["Abby", 10, 100], ["Ben", 50, 70], ["Carla", 60, 70], 
["David", 120, 300]]

The output should be:
[[10, 50, ["Abby"]], [50, 60, ["Abby", "Ben"]], 
[60, 70, ["Abby", "Ben", "Carla"]], [70, 100, ["Abby"]], 
[120, 300, ["David"]]]
*/