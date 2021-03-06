﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using CopterDown.Core;
using CopterDown.Core.Entities;
using CopterDown.Enums;
using CopterDown.Game.Types;

namespace CopterDown.Game
{
    public class HudB : ABehavior
    {
        public HudB() : base(ElementType.VIEW, new State())
        {
        }

        public override void OnMessage(Message msg)
        {
            
        }

        public override void Update(TimeSpan delta, TimeSpan absolute)
        {
            var lives = GameObject.FindAtt<int>(GameAttr.LIVES);
            var score = GameObject.FindAtt<int>(GameAttr.SCORE);
            var weapon = GameObjectManager.Get.FindGameObjectBySubType(Subtypes.CANON).FindAtt<Weapon>(GameAttr.WEAPON);

            TextBlock text = new TextBlock();
            text.Text = "Score: " + score.Value;
            text.FontSize = 20;
            GameLoop._canvas.Children.Add(text);
            Canvas.SetLeft(text, 20);
            Canvas.SetTop(text, 20);
            Canvas.SetZIndex(text, 10);

            text = new TextBlock();
            text.Text = "Lives: " + lives.Value;
            text.FontSize = 20;
            GameLoop._canvas.Children.Add(text);
            Canvas.SetLeft(text, 500);
            Canvas.SetTop(text, 20);
            Canvas.SetZIndex(text, 10);

            text = new TextBlock();
            text.Text = "Weapon: " + weapon.Value.Name;
            text.FontSize = 20;
            GameLoop._canvas.Children.Add(text);
            Canvas.SetLeft(text, 20);
            Canvas.SetTop(text, 60);
            Canvas.SetZIndex(text, 10);
        }
    }
}
