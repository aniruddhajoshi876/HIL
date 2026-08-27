def _hex(value):
    return tuple(int(value[i:i + 2], 16) / 255 for i in (0, 2, 4))


def guiTheme():
    return {
        "color": {
            "background": _hex("1E1E1E"), "panel": _hex("252526"),
            "panelEdge": _hex("3E3E42"), "healthy": _hex("89D185"),
            "electrical": _hex("569CD6"), "waiting": _hex("D7BA7D"),
            "fault": _hex("F48771"), "primaryText": _hex("F0F0F0"),
            "secondaryText": _hex("CCCCCC"), "disabledText": _hex("858585"),
            "highlight": _hex("264F78"), "tabBar": (0.0, 0.0, 0.0),
            "tabBarText": (1.0, 1.0, 1.0), "tabBarInactiveText": _hex("CCCCCC"),
        },
        "font": {"name": "Consolas", "title": 15, "heading": 12, "body": 11, "small": 10},
        "spacing": {"padding": (6, 6, 6, 6), "rowSpacing": 4, "columnSpacing": 6,
                    "toolbarHeight": 34, "stripHeight": 30, "rowHeight": 20, "cardHeight": 54},
        "text": {
            "noData": "--",
            "torqueBanner": "TORQUE SCALE UNVERIFIED - PROVISIONAL PROFILE ephorus3-v1.03-provisional-1over512 (1/512 Nm/count)",
            "capturePending": "CAPTURE PENDING", "cornerLabel": "UNVERIFIED",
        },
    }
