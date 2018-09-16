# PID Controller
## Udacity Self Driving Car - Nano Degree

### 1. Objective
> The objective for this project is to design a PID controller which can safely drive a simulated
car around a track built on the Unity engine.

### 2. P.I.D. Parameters
> The simulator provides the distance from the car's 
current position to the center of the track. This is called the Cross Track Error. Based on the
cross track error, the controller outputs a value for throttle and steering angle. The controller
considers the CTE in 3 different respects.
> * P (proportional error) -- The distance from the car to the center of the track
> * I (integral error) -- The sum of all previous errors over all time steps
> * D (differential error) -- The change in error from one time-step to the next  
>
> The final PID parameters used were PID = ( -1.7, 0.0, -70.0).  
> Each parameter is factored into the total error, which is a weighted sum of the three parameters.
 The greater the total error, the greater the steering angle of the tires needs to be to get back 
 to the center. The steering angle is in the opposite direction of the error.
>
### 3. Tuning
> The three parameters were tuned manually. I started by building my model based on the Q and A
video walk through provided by Udacity. Then, using their model as a base, I tuned the parameters.
By watching the car drive around, and knowing how each parameter contributes to the total error, I
was able to tune the 3 parameters, adjusting one at a time.
>  
> Measuring the proportional error allows us to direct the car back towards the track. If the car
was under-steering, I increased the P coefficient. Using only the porportional error however
leads to overshooting the CTE, and at high speeds leads to very unsafe driving conditions.
>
> Measuring the change in error over time, (Differential Error) allows us to smooth out the driving
of the car. As the car get closer to being on track, the D-error component decreases the magnitude
of the steering angle. This effectively dampens the over-steering caused by the P-error. I tuned the
D-error coefficient by increasing the value until the over-steering was sufficiently dampened.
>
> Measuring the integral of error over time allows us to overcome biases in the car's alignment.
I left the I coefficient at 0. Because the track consists of mostly left hand turns, the car tends
to be to the right of the center of the track. This is because the PID controller is reactive,
instead of proactive. Because of this, the I component of the error continued to grow in magnitude.
The model was attempting to correct for the circular nature of the track. The problem arose whenever
the track turned right instead. The PID controller had accumulated a huge left hand turn bias and
therefor drove off the road on any right hand turns.

### 4. Expectation
> The values were much greater than I expected. Following the project video, the coefficients were
all between 0-3. I expected the values to end up in a similar range. However, as I kept pushing the
car to drive faster, it was necessary to react more strongly to error. A small magnitude steering
angle was not sufficient to get the car back on track at high speeds. Increasing the magnitude of
the P component necessitated an even greater increase in the magnitude of the D component.
> 
> I was able to maximize the velocity around the track by setting the throttle control proportionally
to the CTE as well. At first, I tried implementing a PID controller for the throttle, but found that
a 1/x^2 curve was a better model for throttle control. It was responsive to changes in CTE and
allowed the car to accelerate out of a curve. The car was able to attain a top speed of around 75 mph
on the second lap.

### 5. Video
> A video of my car driving around the track can be found [here](./self_driving_car_nanodegree_program%209_17_2018%201_19_44%20AM.mp4)
> Or [here](https://youtu.be/w_TzpFNDRjw)