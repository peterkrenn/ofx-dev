# http://wiki.github.com/jashkenas/ruby-processing

class Pong < Processing::App
  def setup
    smooth
    ellipse_mode CENTER
    no_fill
    stroke 255

    @left_paddle = Paddle.new(200, 200)
    @right_paddle = Paddle.new(600, 200)
    @ball = Ball.new(400, 200)
  end

  def draw
    background 0

    collide_with_boundaries
    collide_with_paddles
    @ball.move

    @left_paddle.draw
    @right_paddle.draw
    @ball.draw
  end

  def key_pressed
    case key
      when 'a':
        @left_paddle.move_up
      when 'z':
        @left_paddle.move_down
      when '\'':
        @right_paddle.move_up
      when '/':
        @right_paddle.move_down
    end
  end

  def collide_with_boundaries
    if @ball.position.x <= @ball.radius || @ball.position.x >= width - @ball.radius
      @ball.velocity.x *= -1
    elsif @ball.position.y <= @ball.radius || @ball.position.y >= height - @ball.radius
      @ball.velocity.y *= -1
    end
  end

  def collide_with_paddles
    [@left_paddle, @right_paddle].each do |paddle|
      distance_vector = @ball.position - paddle.position
      next unless (@ball.radius + paddle.radius) ** 2 > distance_vector.squared_magnitude

      normal = distance_vector.normal.normalized
      @ball.velocity = normal * (@ball.velocity * normal) * 2 - @ball.velocity
    end
  end

  class Paddle
    attr_accessor :position, :radius

    def initialize(x, y)
      @position = Vector.new(x, y)
      @radius = 20
    end

    def draw
      $app.stroke_weight 2
      $app.ellipse @position.x, @position.y, @radius * 2, @radius * 2
    end

    def move_up
      @position.y -= 10 unless @position.y <= @radius
    end

    def move_down
      @position.y += 10 unless @position.y >= $app.height - @radius
    end
  end

  class Ball
    attr_accessor :position, :velocity, :radius

    def initialize(x, y)
      @position = Vector.new(x, y)
      # @velocity = Vector.new(rand * 2 - 2, rand * 2 - 2)
      @velocity = Vector.new(1, 0)
      @radius = 5
    end

    def draw
      $app.stroke_weight 1
      $app.ellipse @position.x, @position.y, @radius * 2, @radius * 2
    end

    def move
      @position += @velocity
    end
  end

  class Vector
    attr_accessor :x, :y

    def initialize(x, y)
      @x, @y = x, y
    end

    def +(other)
      if other.is_a?(Numeric)
        Vector.new(@x + other, @y + other)
      elsif other.is_a?(Vector)
        Vector.new(@x + other.x, @y + other.y)
      else
        self
      end
    end

    def -(other)
      if other.is_a?(Numeric)
        Vector.new(@x - other, @y - other)
      elsif other.is_a?(Vector)
        Vector.new(@x - other.x, @y - other.y)
      else
        self
      end
    end

    def *(other)
      if other.is_a?(Numeric)
        Vector.new(@x * other, @y * other)
      elsif other.is_a?(Vector)
        @x * other.x + @y * other.y
      else
        self
      end
    end

    def magnitude
      Math::sqrt(@x * @x + @y * @y)
    end
      
    def squared_magnitude
      @x * @x + @y * @y
    end

    def normal
      Vector.new(-@y, @x)
    end

    def normalized
      magnitude = self.magnitude
      Vector.new(@x / magnitude, @y / magnitude)
    end
  end
end

$app = Pong.new :width => 800, :height => 400, :title => 'Pong'
