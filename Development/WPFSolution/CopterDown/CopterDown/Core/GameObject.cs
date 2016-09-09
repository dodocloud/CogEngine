﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using CopterDown.Behavior;

namespace CopterDown.Core
{
    public class GameObject
    {
        private GameObject _parent;

        public GameObject( GameObject parent)
        {
            this._parent = parent;
            Attributes = new List<Attribute>();
            Behaviors = new List<ABehavior>();
            Children = new List<GameObject>();
        }

        public void OnMessage(Message msg)
        {
            foreach(var child in Children) child.OnMessage(msg);

            foreach(var beh in Behaviors) beh.OnMessage(msg);
        }

        public void Update(TimeSpan delta, TimeSpan absolute)
        {
            foreach (var child in Children) child.Update(delta, absolute);

            foreach (var beh in Behaviors) beh.Update(delta,absolute);
        }

        public List<Attribute> Attributes { get; set; }
 
        public List<ABehavior> Behaviors { get; set; }

        public List<GameObject> Children { get; set; }
    }
}
