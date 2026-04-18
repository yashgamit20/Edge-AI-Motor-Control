import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from sklearn.linear_model import LinearRegression
from sklearn.preprocessing import PolynomialFeatures

df = pd.read_csv("data_cleaned.csv")
X = df[["Temp"]]
y = df["Speed"]

# Polynomial degree 3
poly = PolynomialFeatures(degree=3)
X_poly = poly.fit_transform(X)

model = LinearRegression()
model.fit(X_poly, y)

c = model.coef_
i = model.intercept_

print("POLY EQUATION:")
print(f"Speed = {c[3]:.4f}*T^3 + ({c[2]:.4f})*T^2 + ({c[1]:.4f})*T + {i:.4f}")

# Plot
X_range = np.linspace(X.min(), X.max(), 100).reshape(-1, 1)
X_range_poly = poly.transform(X_range)
y_pred = model.predict(X_range_poly)

plt.figure(figsize=(8,5))
plt.scatter(df["Temp"], df["Speed"], color="blue", label="Clean Data")
plt.plot(X_range, y_pred, color="red", label="Poly Fit (3rd Degree)")
plt.xlabel("Temperature (C)")
plt.ylabel("Speed (1-8)")
plt.title("Temperature vs Speed Model (Polynomial)")
plt.legend()
plt.grid()
plt.savefig("model_plot.png")
