import Qt 4.7

Grid {
    columns: 2
    spacing: 2

    Ellipse {
        border.color: "black"
        color: "#88e"
        gradient: Gradient { GradientStop { position: 0.0; color: "#fff" }
                             GradientStop { position: 1.0; color: "#aaf" } }
    }
    Ellipse {
        border.color: "black"
        color: "#88f"
    }
    Ellipse {
        border.color: "black"
        color: "#44a"
    }
    Ellipse {
        border.color: "black"
        color: "#44c"
    }
}
